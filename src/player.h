#ifndef PLAYER_H
#define PLAYER_H

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

typedef struct Player{
    int x;
    int y;
    int width;
    int height;
    SDL_Rect rect;
    direction dir;
    int speed;
    int health;
    int score;
    bool active;
} Player;

Player playerCreate(int x, int y, int width, int height, int speed, int health, int score);
void playerMove(Player* player, const Uint8* state, int playerspeed);
void playerCombat(Player* player, const Uint8* state);


#endif // PLAYER_H