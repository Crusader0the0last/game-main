#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include <stdbool.h>

typedef enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPLEFT,
    UPRIGHT,
    DOWNLEFT,
    DOWNRIGHT
} direction;

typedef struct Bullet{
    int x;
    int y;
    int width;
    int height;
    SDL_Rect rect;
    direction dir;
    int speed;
    bool active;
} Bullet;

Bullet bulletCreate(int x, int y, int width, int height, int speed);
void bulletMove(Bullet* bullet, direction dir, int playerX, int playerY);
void bulletDirection(Bullet* bullet, direction dir, const Uint8* state);

#endif // BULLET_H