# Symbols

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `BEACON_INTERVAL` | macro | `phantom.c:45` | `#define BEACON_INTERVAL` |
| `CMD_BUFFER_SIZE` | macro | `phantom.c:48` | `#define CMD_BUFFER_SIZE` |
| `DEFAULT_PORT` | macro | `phantom.c:43` | `#define DEFAULT_PORT` |
| `DEFAULT_SERVER` | macro | `phantom.c:42` | `#define DEFAULT_SERVER` |
| `ENCRYPT_KEY` | macro | `phantom.c:44` | `#define ENCRYPT_KEY` |
| `IO_URING_QUEUE_DEPTH` | macro | `phantom.c:47` | `#define IO_URING_QUEUE_DEPTH` |
| `JITTER_PERCENT` | macro | `phantom.c:46` | `#define JITTER_PERCENT` |
| `MAX_PATH` | macro | `phantom.c:49` | `#define MAX_PATH` |
| `_GNU_SOURCE` | macro | `phantom.c:7` | `#define _GNU_SOURCE` |
| `__io_uring_enter` | function | `phantom.c:72` | `static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
   ...` |
| `__io_uring_register` | function | `phantom.c:76` | `static inline int __io_uring_register(int fd, unsigned int opcode, const void *arg, unsigned int ...` |
| `__io_uring_setup` | function | `phantom.c:69` | `static inline int __io_uring_setup(unsigned int entries, struct io_uring_params *p)` |
| `anti_forensics` | function | `phantom.c:600` | `static void anti_forensics(void)` |
| `c2_command_t` | struct | `phantom.c:171` | `` |
| `c2_loop` | function | `phantom.c:563` | `static void *c2_loop(void *arg)` |
| `c2_response_t` | struct | `phantom.c:177` | `` |
| `chacha20_keystream` | function | `phantom.c:155` | `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size...` |
| `connect_c2` | function | `phantom.c:409` | `static int connect_c2(void)` |
| `download_file` | function | `phantom.c:319` | `static int download_file(const char *remote_path, const char *local_path)` |
| `encrypt_payload` | function | `phantom.c:161` | `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce)` |
| `install_persistence` | function | `phantom.c:326` | `static void install_persistence(void)` |
| `io_uring` | struct | `phantom.c:62` | `` |
| `io_uring_cq` | struct | `phantom.c:58` | `` |
| `io_uring_sq` | struct | `phantom.c:54` | `` |
| `main` | function | `phantom.c:611` | `int main(int argc, char **argv)` |
| `process_command` | function | `phantom.c:462` | `static void process_command(int sock, c2_command_t *cmd)` |
| `recv_command` | function | `phantom.c:441` | `static c2_command_t recv_command(int sock)` |
| `recv_encrypted` | function | `phantom.c:424` | `static int recv_encrypted(int sock, void *buf, size_t len, unsigned char *key)` |
| `run_shell_command` | function | `phantom.c:268` | `static char *run_shell_command(const char *cmd)` |
| `send_encrypted` | function | `phantom.c:431` | `static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key)` |
| `send_response` | function | `phantom.c:453` | `static void send_response(int sock, c2_response_t *resp)` |
| `take_screenshot` | function | `phantom.c:400` | `static void take_screenshot(const char *outfile)` |
| `upload_file` | function | `phantom.c:303` | `static int upload_file(const char *local_path, const char *remote_path)` |
| `uring_cqe_seen` | function | `phantom.c:143` | `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe)` |
| `uring_get_sqe` | function | `phantom.c:120` | `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)` |
| `uring_queue_init` | function | `phantom.c:80` | `static int uring_queue_init(unsigned int entries, struct io_uring *ring)` |
| `uring_read` | function | `phantom.c:221` | `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)` |
| `uring_submit` | function | `phantom.c:128` | `static int uring_submit(struct io_uring *ring)` |
| `uring_wait_cqe_timeout` | function | `phantom.c:134` | `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeo...` |
| `uring_write` | function | `phantom.c:243` | `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)` |
| `main` | function | `server.py:25` | `def main()` |
| `recv_exact` | function | `server.py:15` | `def recv_exact(sock, n)` |
| `xor_crypt` | function | `server.py:11` | `def xor_crypt(data)` |
