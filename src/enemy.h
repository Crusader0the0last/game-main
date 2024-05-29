#ifndef ENEMY_H
#define ENEMY_H

#include "player.h"

typedef struct Enemy{
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
}Enemy;

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

Enemy* createSimpleEnemy(int x, int y, int width, int height, int health, int speed);
Boss* createBoss(int x, int y, int width, int height, int speed);
enemyBullet* createEnemyBullet(int x, int y, int width, int height, int speed, direction dir);

void moveEnemy(Enemy* enemy);
void moveBoss(Boss* boss);
void updateEnemyBullet(enemyBullet* bullet);

void enemyCombat(Enemy* enemy, enemyBullet* bullet, Player player);
void bossCombat(Boss* boss, enemyBullet* bullet, Player player);


#endif // ENEMY_H