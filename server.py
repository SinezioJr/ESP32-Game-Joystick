import socket
import threading

import pyautogui


def hold_Key(key, hold_time):
    import time
    import pyautogui
    start = time.time()
    while time.time() - start < hold_time:
        pyautogui.press(key)


def handle_client(sock, data, address):
    switcher = {
        "U": "W",
        "D": "S",
        "R": "D",
        "L": "A",
    }

    mensage = data.decode()
    print(f"Received '{mensage}' from {address}")

    comands = mensage.split(",")

    for cm in comands:
        if (cm in switcher.keys()):
            print(f"Execute the function '{switcher[cm]}'")
            hold_Key(switcher[cm], 50)


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
