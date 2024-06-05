#ifndef SACRED_H
#define SACRED_H

#include "player.h"

//struktura totemu
typedef struct Totem{
    int health;
    int x;
    int y;
    int width;
    int height;
    int frame;
    bool isAlive;
    bool moving;
    bool isShooting;
    bool isHit;
    SDL_Texture *main;
    SDL_Texture *death;
}Totem;

Totem* createtotem(int x, int y, int width, int height, int health);

#endif // SACRED_H;