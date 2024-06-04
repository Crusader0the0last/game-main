#include "enemy.h"

skeleton* createSkeleton(int x, int y, int width, int height, int health, int speed){
    skeleton* enemy = (skeleton*)malloc(sizeof(skeleton));
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
    enemy->walk = NULL;
    enemy->idle = NULL;
    enemy->attack = NULL;
    enemy->dead = NULL;
    return enemy;
}

void moveSkeleton(skeleton* enemy){
    if(enemy->isAlive == true){
        if(enemy->x>0){
            enemy->x -= enemy->speed;
            enemy->dir = LEFT;
            enemy->moving = true;
        }
        if(enemy->x<0){
            enemy->x += enemy->speed;
            enemy->dir = RIGHT;
            enemy->moving = true;
        }
        if(enemy->y > 350){
            enemy->y -= enemy->speed;
            enemy->moving = true;
        }
        if(enemy->y < 350){
            enemy->y += enemy->speed;
            enemy->moving = true;
        }
    }
}

void skeletonCombat(skeleton* enemy, Player* player, Bullet* bullet){
    if(bullet->x >= (enemy->x - 75) && bullet->x <= (enemy->x + 50) && bullet->y >= (enemy->y - 50)&& bullet->y <= (enemy->y + 80) && enemy->isAlive == true && bullet->isActive == true){
        bullet->isActive = false;
        enemy->health -= 50;
        if(enemy->health <= 0){
            enemy->frame = 0;
        }
        bullet->frame = 0;
    }
    if(player->x >= (enemy->x - 75) && player->x <= (enemy->x + 50) && player->y >= (enemy->y - 50)&& player->y <= (enemy->y + 80) && enemy->isAlive == true){
        player->health -= 10;
    }
    if(enemy->health <= 0){
        enemy->isAlive = false;
    }
}

goblin* createGoblin(int x, int y, int width, int height, int health, int speed){
    goblin* enemy = (goblin*)malloc(sizeof(goblin));
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
    enemy->walk = NULL;
    enemy->idle = NULL;
    enemy->attack = NULL;
    enemy->dead = NULL;
    return enemy;
}

void moveGoblin(goblin* enemy){
    if(enemy->isAlive == true){
        if(enemy->x>0){
            enemy->x -= enemy->speed;
            enemy->dir = LEFT;
            enemy->moving = true;
        }
        if(enemy->x<0){
            enemy->x += enemy->speed;
            enemy->dir = RIGHT;
            enemy->moving = true;
        }
        if(enemy->y > 350){
            enemy->y -= enemy->speed;
            enemy->moving = true;
        }
        if(enemy->y < 350){
            enemy->y += enemy->speed;
            enemy->moving = true;
        }
    }
}
void goblinCombat(goblin* enemy, Player* player, Bullet* bullet){
    if(bullet->x >= (enemy->x - 75) && bullet->x <= (enemy->x + 50) && bullet->y >= (enemy->y - 20)&& bullet->y <= (enemy->y + 40) && enemy->isAlive == true && bullet->isActive == true){
        bullet->isActive = false;
        enemy->health -= 50;
        if(enemy->health <= 0){
            enemy->frame = 0;
        }
        bullet->frame = 0;
    }
    if(player->x >= (enemy->x - 75) && player->x <= (enemy->x + 50) && player->y >= (enemy->y - 50)&& player->y <= (enemy->y + 80) && enemy->isAlive == true){
        player->health -= 10;
    }
    if(enemy->health <= 0){
        enemy->isAlive = false;
    }
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
