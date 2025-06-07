# pip install pygame, if needed. 

import pygame

# Alusta pygame
pygame.init()

# Ikkunan koko
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Siirrä suorakulmioita hiirellä (ei päällekkäin)")

# Värit
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

# Suorakulmiot (x, y, width, height)
rect1 = pygame.Rect(100, 100, 150, 100)
rect2 = pygame.Rect(300, 200, 150, 100)

# Muuttujat vetämiseen
dragging = None
offset_x = 0
offset_y = 0

# Pääsilmukka
running = True
clock = pygame.time.Clock()

def rectangles_overlap(r1, r2):
    return r1.colliderect(r2)

while running:
    screen.fill(WHITE)

    # Piirrä suorakulmiot
    pygame.draw.rect(screen, RED, rect1)
    pygame.draw.rect(screen, BLUE, rect2)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        elif event.type == pygame.MOUSEBUTTONDOWN:
            if rect1.collidepoint(event.pos):
                dragging = rect1
                offset_x = rect1.x - event.pos[0]
                offset_y = rect1.y - event.pos[1]
            elif rect2.collidepoint(event.pos):
                dragging = rect2
                offset_x = rect2.x - event.pos[0]
                offset_y = rect2.y - event.pos[1]

        elif event.type == pygame.MOUSEBUTTONUP:
            dragging = None

        elif event.type == pygame.MOUSEMOTION:
            if dragging:
                new_x = event.pos[0] + offset_x
                new_y = event.pos[1] + offset_y
                old_rect = dragging.copy()
                dragging.x = new_x
                dragging.y = new_y

                # Estetään päällekkäisyys siirron jälkeen
                if (dragging == rect1 and rectangles_overlap(rect1, rect2)) or \
                   (dragging == rect2 and rectangles_overlap(rect1, rect2)):
                    dragging.x = old_rect.x
                    dragging.y = old_rect.y

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
