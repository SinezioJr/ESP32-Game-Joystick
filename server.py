import socket

HOST = '' # listen on all available network interfaces
PORT = 8000 # the same port as in the ESP32 code

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print('Server is listening on port', PORT)
    
    while True:
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            data = conn.recv(1024)
            print('Received:', data.decode())
