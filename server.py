import socket
import threading


def handle_client(sock, data, address):
    switcher = {
        "A": "function_A",
        "B": "function_B"
    }

    mensage = data.decode()
    print(f"Received '{mensage}' from {address}")

    if (mensage in switcher.keys()):
        print(f"Execute the function '{switcher[mensage]}'")


def start_server():
    # set up UDP socket
    server_address = ('', 5005)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(server_address)

    print("Server started.")

    # handle incoming messages in separate threads
    while True:
        data, address = sock.recvfrom(1024)
        client_thread = threading.Thread(
            target=handle_client, args=(sock, data, address))
        client_thread.start()


if __name__ == "__main__":
    start_server()
