#include "sacred.h"

Totem* createtotem(int x, int y, int width, int height, int health){
    Totem* totem = (Totem*)malloc(sizeof(Totem));
    totem->x = x;
    totem->y = y;
    totem->width = width;
    totem->height = height;
    totem->health = health;
    totem->isAlive = true;
    totem->isShooting = false;
    totem->frame = 0;
    return totem;
}



