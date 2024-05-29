#include "enemy.h"

Enemy* createSimpleEnemy(int x, int y, int width, int height, int health, int speed){
    Enemy* enemy = (Enemy*)malloc(sizeof(Enemy));
    enemy->x = x;
    enemy->y = y;
    enemy->width = width;
    enemy->height = height;
    enemy->health = health;
    enemy->speed = speed;
    enemy->dir = LEFT;
    enemy->isAlive = true;
    enemy->moving = false;
    enemy->isAttacking = false;
    enemy->frame = 0;
    return enemy;
}

Boss* createBoss(int x, int y, int width, int height, int speed){
    Boss* boss = (Boss*)malloc(sizeof(Boss));
    boss->x = x;
    boss->y = y;
    boss->width = width;
    boss->height = height;
    boss->speed = speed;
    boss->dir = LEFT;
    boss->isActive = true;
    boss->hit = false;
    boss->bossPhase = 1;
    boss->frame = 0;
    return boss;
}

void moveEnemy(Enemy* enemy){
    if(enemy->x>0){
        enemy->x -= enemy->speed;
        enemy->dir = LEFT;
    }
    if(enemy->x<0){
        enemy->x += enemy->speed;
        enemy->dir = RIGHT;
    }
    if(enemy->y > 350){
        enemy->y -= enemy->speed;
    }
    if(enemy->y < 350){
        enemy->y += enemy->speed;
    }
}