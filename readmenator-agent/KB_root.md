# Subsystem: root

## compile_run.sh
- Layer: utility
- Language: sh

## phantom.c
- Layer: utility
- Language: c
- Symbols:
  - `io_uring_sq` (struct, line 54)
  - `io_uring_cq` (struct, line 58)
  - `io_uring` (struct, line 62)
  - `__io_uring_setup` (function, line 68) `static inline int __io_uring_setup(unsigned int entries, struct io_uring_params *p)`
  - `__io_uring_enter` (function, line 72) `static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
   ...`
  - `__io_uring_register` (function, line 76) `static inline int __io_uring_register(int fd, unsigned int opcode, const void *arg, unsigned int ...`
  - `uring_queue_init` (function, line 79) `static int uring_queue_init(unsigned int entries, struct io_uring *ring)`
  - `uring_get_sqe` (function, line 119) `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)`
  - `uring_submit` (function, line 127) `static int uring_submit(struct io_uring *ring)`
  - `uring_wait_cqe_timeout` (function, line 133) `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeo...`
  - `uring_cqe_seen` (function, line 142) `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe)`
  - `chacha20_keystream` (function, line 154) `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size...`
  - `encrypt_payload` (function, line 160) `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce)`
  - `uring_read` (function, line 220) `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)`
  - `uring_write` (function, line 242) `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)`
  - `run_shell_command` (function, line 268) `static char *run_shell_command(const char *cmd)`
  - `upload_file` (function, line 303) `static int upload_file(const char *local_path, const char *remote_path)`
  - `download_file` (function, line 318) `static int download_file(const char *remote_path, const char *local_path)`
  - `install_persistence` (function, line 326) `static void install_persistence(void)`
  - `take_screenshot` (function, line 400) `static void take_screenshot(const char *outfile)`
  - `connect_c2` (function, line 409) `static int connect_c2(void)`
  - `recv_encrypted` (function, line 423) `static int recv_encrypted(int sock, void *buf, size_t len, unsigned char *key)`
  - `send_encrypted` (function, line 430) `static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key)`
  - `recv_command` (function, line 440) `static c2_command_t recv_command(int sock)`
  - `send_response` (function, line 452) `static void send_response(int sock, c2_response_t *resp)`
  - `process_command` (function, line 462) `static void process_command(int sock, c2_command_t *cmd)`
  - `c2_loop` (function, line 563) `static void *c2_loop(void *arg)`
  - `anti_forensics` (function, line 600) `static void anti_forensics(void)`
  - `main` (function, line 611) `int main(int argc, char **argv)`
  - `_GNU_SOURCE` (macro, line 6)
  - `DEFAULT_SERVER` (macro, line 42)
  - `DEFAULT_PORT` (macro, line 43)
  - `ENCRYPT_KEY` (macro, line 44)
  - `BEACON_INTERVAL` (macro, line 45)
  - `JITTER_PERCENT` (macro, line 46)
  - `IO_URING_QUEUE_DEPTH` (macro, line 47)
  - `CMD_BUFFER_SIZE` (macro, line 48)
  - `MAX_PATH` (macro, line 49)

## server.py
- Layer: utility
- Language: py
- Symbols:
  - `xor_crypt` (function, line 11) `def xor_crypt(data)`
  - `recv_exact` (function, line 15) `def recv_exact(sock, n)`
  - `main` (function, line 25) `def main()`
