from ctypes.wintypes import RECT
import pygame

pygame.init()

SCREEN_HEIGHT = 600
SCREEN_WIDTH = 1100
SCREEN = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))


# print(pygame.font.get_fonts())
def dinoGame():
    color = (0,128, 255)
    run = True
    clock = pygame.time.Clock()

    while run:


        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
        pygame.draw.rect(SCREEN , color, pygame.Rect(30, 40, 50, 60));
        processedKey = pygame.key.pygame.key.get_pressed()
        if(processedKey[pygame.])

        clock.tick(60)
        pygame.display.set_caption('Chrome Dino')
        pygame.display.update()


dinoGame()