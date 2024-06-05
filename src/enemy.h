#ifndef ENEMY_H
#define ENEMY_H

#include "sacred.h"

typedef struct Goblin{
    int health;
    int speed;
    int x;
    int y;
    int width;
    int height;
    direction dir;
    bool isAlive;
    bool moving;
    bool isAttacking;
    int frame;
    SDL_Texture *walk;
    SDL_Texture *idle;
    SDL_Texture *attack;
    SDL_Texture *hit;
    SDL_Texture *dead;
}goblin;

typedef struct Skeleton{
    int health;
    int speed;
    int x;
    int y;
    int width;
    int height;
    direction dir;
    bool isAlive;
    bool moving;
    bool isAttacking;
    int frame;
    SDL_Texture *walk;
    SDL_Texture *idle;
    SDL_Texture *attack;
    SDL_Texture *hit;
    SDL_Texture *dead;
}skeleton;

typedef struct Boss{
    int x;
    int y;
    int width;
    int height;
    int speed;
    direction dir;
    bool isActive;
    bool hit;
    int bossPhase;
    int frame;
}Boss;

typedef struct enemyBullet{
    int x;
    int y;
    int width;
    int height;
    int speed;
    direction dir;
    bool isActive;
    bool hit;
    int frame;
}enemyBullet;

skeleton* createSkeleton(int x, int y, int width, int height, int health, int speed);
Boss* createBoss(int x, int y, int width, int height, int speed);
goblin* createGoblin(int x, int y, int width, int height, int health, int speed);

enemyBullet* createEnemyBullet(int x, int y, int width, int height, int speed, direction dir);

void moveSkeleton(skeleton* enemy);
void moveGoblin(goblin* enemy);
void moveBoss(Boss* boss);
void updateEnemyBullet(enemyBullet* bullet);

void skeletonCombat(skeleton* enemy, Player* player, Bullet* bullet, Totem* totem);
void goblinCombat(goblin* enemy, Player* player, Bullet* bullet);

void bossCombat(Boss* boss, enemyBullet* bullet, Player player);


#endif // ENEMY_H;