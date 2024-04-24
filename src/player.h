#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <stdbool.h>

typedef struct Player{
    int x;
    int y;
    int width;
    int height;
    SDL_Rect rect;
    int speed;
    int health;
    int score;
    bool active;
} Player;

Player playerCreate(int x, int y, int width, int height, int speed, int health, int score);
void playerMove(Player* player, const Uint8* state);
void playerCombat(Player* player, const Uint8* state);


#endif // PLAYER_H