#ifndef ENTITY_TEXTURES_H
#define ENTITY_TEXTURES_H

#include <SDL.h>
#include <stdbool.h>
#include "player.h"
#include "enemy.h"
#include "bullet.h"

typedef struct playerTexture {
    SDL_Texture* playerTexture;
    const char *playerTexturePath;
    SDL_Rect playerRect;
    SDL_Rect playerSprite;
    bool playerActive;
    bool playerMoving;
    direction playerDir;
} playerTexture;

playerTexture textureLoad(SDL_Renderer* renderer, bool dead, bool moving, int width, int height, direction dir);

#endif // ENTITY_TEXTURES_H