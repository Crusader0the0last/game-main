#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

//struktura smeru (bude urcovat smer textur a pohybu strel)
typedef enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPRIGHT,
    UPLEFT,
    DOWNRIGHT,
    DOWNLEFT
}direction;

//struktura strel hrace
typedef struct Bullet{
    int x;
    int y;
    int width;
    int height;
    int speed;
    direction dir;
    bool isActive;
    bool hit;
    int frame;
    int damage;
    int angle;
}Bullet;

//struktura hrace
typedef struct Player{
    int health;
    int speed;
    int score;
    int x;
    int y;
    int width;
    int height;
    int frame;
    direction dir;
    bool isAlive;
    bool moving;
    bool isShooting;
    bool isHit;
    SDL_Texture *walk;
    SDL_Texture *idle;
    SDL_Texture *attack;
    SDL_Texture *hit;
    SDL_Texture *dead;
}Player;

Player* createPlayer(int x, int y, int width, int height, int health, int speed, int score);
Bullet* createBullet(int x, int y, int width, int height, int speed, direction dir);

void movePlayer(Player* player, direction dir);
void combatPlayer(Player* player, Bullet* bullet);
void updateBullet(Bullet* bullet, Player* player);

void updatePlayer(Player* player);
void destroyPlayer(Player* player);


#endif // PLAYER_H