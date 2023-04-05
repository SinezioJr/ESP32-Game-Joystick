import pygame
import socket
import threading

pygame.init()

# Configurações da tela
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
clock = pygame.time.Clock()

player_pos = [screen_width/2, screen_height/2]


class UDPThread(threading.Thread):
    def __init__(self):
        super().__init__()
        self.running = True
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind(('', 5005))
        self.last_data = {
            "1": [screen_width/2-10, screen_height/2], "2": [screen_width/2+10, screen_height/2]}

    def run(self):
        switcher = {
            "U": 2,
            "D": -2,
            "L": 2,
            "R": -2,
        }

        while self.running:
            data, addr = self.sock.recvfrom(1024)
            id_, directions = data.decode().split("-")
            if directions:
                comands = directions.split(",")
                for i, cm in enumerate(comands):
                    if cm in switcher.keys():
                        self.last_data[id_][i] += switcher[comands[i]]

    def stop(self):
        self.running = False

    def get_last_data(self):
        return self.last_data

    def mark_last_data(self):
        self.last_data = None


# Cria e inicia a thread UDP
udp_thread = UDPThread()
udp_thread.start()

# Loop principal do jogo
running = True
while running:
    # Verifica se há eventos do teclado
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            # Sai do jogo se o usuário fechar a janela
            running = False

    player_pos = udp_thread.get_last_data()

    # Renderização do jogo
    screen.fill((255, 255, 255))

    # Limitar a posição do personagem para dentro da tela
    for id_ in player_pos.keys():
        if player_pos[id_][0] < 0:
            player_pos[id_][0] = 0
        if player_pos[id_][0] > screen_width:
            player_pos[id_][0] = screen_width
        if player_pos[id_][1] < 0:
            player_pos[id_][1] = 0
        if player_pos[id_][1] > screen_height:
            player_pos[id_][1] = screen_height

        # Desenha o personagem
        if (id_ == "1"):
            color = (255, 0, 0)
        else:
            color = (0, 0, 255)
        pygame.draw.circle(screen, color, player_pos[id_], 10)

    # Atualiza a tela
    pygame.display.flip()
