#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

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
}Bullet;

typedef struct Player{
    int health;
    int speed;
    int score;
    int x;
    int y;
    int width;
    int height;
    direction dir;
    bool isAlive;
    bool moving;
    bool isShooting;

}Player;

Player* createPlayer(int x, int y, int width, int height, int health, int speed, int score);
Bullet* createBullet(int x, int y, int width, int height, int speed, direction dir);

void movePlayer(Player* player, direction dir);
void combatPlayer(Player* player, Bullet* bullet);
void updateBullet(Bullet* bullet, Player* player);

void updatePlayer(Player* player);
void destroyPlayer(Player* player);

#endif // PLAYER_H