# API

## phantom.c
- `uring_queue_init` (function) `phantom.c:80` `static int uring_queue_init(unsigned int entries, struct io_uring *ring)`
- `uring_get_sqe` (function) `phantom.c:120` `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)`
- `uring_submit` (function) `phantom.c:128` `static int uring_submit(struct io_uring *ring)`
- `uring_wait_cqe_timeout` (function) `phantom.c:134` `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeo...`
- `uring_cqe_seen` (function) `phantom.c:143` `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe)`
- `chacha20_keystream` (function) `phantom.c:155` `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size...`
- `encrypt_payload` (function) `phantom.c:161` `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce)`
- `uring_read` (function) `phantom.c:221` `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)`
- `uring_write` (function) `phantom.c:243` `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)`
- `run_shell_command` (function) `phantom.c:268` `static char *run_shell_command(const char *cmd)`
- `upload_file` (function) `phantom.c:303` `static int upload_file(const char *local_path, const char *remote_path)`
- `download_file` (function) `phantom.c:319` `static int download_file(const char *remote_path, const char *local_path)`
- `install_persistence` (function) `phantom.c:326` `static void install_persistence(void)`
- `take_screenshot` (function) `phantom.c:400` `static void take_screenshot(const char *outfile)`
- `connect_c2` (function) `phantom.c:409` `static int connect_c2(void)`
- `recv_encrypted` (function) `phantom.c:424` `static int recv_encrypted(int sock, void *buf, size_t len, unsigned char *key)`
- `send_encrypted` (function) `phantom.c:431` `static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key)`
- `recv_command` (function) `phantom.c:441` `static c2_command_t recv_command(int sock)`
- `send_response` (function) `phantom.c:453` `static void send_response(int sock, c2_response_t *resp)`
- `process_command` (function) `phantom.c:462` `static void process_command(int sock, c2_command_t *cmd)`
- `c2_loop` (function) `phantom.c:563` `static void *c2_loop(void *arg)`
- `anti_forensics` (function) `phantom.c:600` `static void anti_forensics(void)`
- `main` (function) `phantom.c:611` `int main(int argc, char **argv)`

## server.py
- `xor_crypt` (function) `server.py:11` `def xor_crypt(data)` -- Aplica XOR con la clave definida
- `recv_exact` (function) `server.py:15` `def recv_exact(sock, n)` -- Recibe exactamente n bytes
- `main` (function) `server.py:25` `def main()`
