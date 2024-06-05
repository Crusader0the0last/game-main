#include "enemy.h"

//vytvareni jednotlivich kostlivcu
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

//pohyb kostlivce
void moveSkeleton(skeleton* enemy){
    if(enemy->isAlive == true){
        if(enemy->x>100){
            enemy->x -= enemy->speed;
            enemy->dir = LEFT;
            enemy->moving = true;
        }
        if(enemy->x<0){
            enemy->x += enemy->speed;
            enemy->dir = RIGHT;
            enemy->moving = true;
        }
        if(enemy->y > 250){
            enemy->y -= enemy->speed;
            enemy->moving = true;
        }
        if(enemy->y < 250){
            enemy->y += enemy->speed;
            enemy->moving = true;
        }
    }
}

//combat kostlivce
void skeletonCombat(skeleton* enemy, Player* player, Bullet* bullet, Totem* totem){
    if(bullet->x >= (enemy->x - 75) && bullet->x <= (enemy->x + 50) && bullet->y >= (enemy->y - 50)&& bullet->y <= (enemy->y + 50) && enemy->isAlive == true && bullet->isActive == true){
        bullet->isActive = false;
        enemy->health -= 50;
        if(enemy->health <= 0){
            enemy->frame = 0;
        }
        bullet->frame = 0;
    }
    if(enemy->health <= 0){
        enemy->isAlive = false;
    }
    if(player->isAlive == false){
        player->isHit == false;
    }
    //utok na hrace
    if(player->x >= (enemy->x - 85) && player->x <= (enemy->x + 60) && player->y >= (enemy->y - 120)&& player->y <= (enemy->y + 40) && enemy->isAlive == true && player->isHit == false && player->isAlive == true){
        if(enemy->frame = 6){
            player->health -= 15;
            player->isHit = true;
            player->frame = 0;
        }
        if(player->health <= 0){
            player->isAlive = false;
            player->frame = 0;
        }
        enemy->isAttacking = true;
    }
    else if (player->x < enemy->x - 85 || player->x > enemy->x + 60 || player->y < enemy->y - 120 || player->y > enemy->y + 40 || enemy->isAlive != true || player->isAlive != true){
        enemy->isAttacking = false;
    }
    //utok na totem
    if(totem->x >= (enemy->x - 85) && totem->x <= (enemy->x + 60) && totem->y >= (enemy->y - 120) && totem->y <= (enemy->y + 40) && enemy->isAlive == true && totem->isHit == false && totem->isAlive == true){
        if(enemy->frame = 6){
            totem->health -= 30;
            totem->isHit = true;
            totem->frame = 0;
        }
        if(totem->health <= 0){
            totem->isAlive = false;
            totem->frame = 0;
        }
        enemy->isAttacking = true;
    }
}

//vytvareni jednotlivich goblinu
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

//pohyb goblina
void moveGoblin(goblin* enemy){
    if(enemy->isAlive == true){
        if(enemy->x>100){
            enemy->x -= enemy->speed;
            enemy->dir = LEFT;
            enemy->moving = true;
        }
        if(enemy->x<0){
            enemy->x += enemy->speed;
            enemy->dir = RIGHT;
            enemy->moving = true;
        }
        if(enemy->y > 250 && enemy->y >= enemy->x){
            enemy->y -= enemy->speed;
            enemy->moving = true;
        }
        if(enemy->y < 250 && enemy->y >= enemy->x){
            enemy->y += enemy->speed;
            enemy->moving = true;
        }
    }
}

//combat goblina
void goblinCombat(goblin* enemy, Player* player, Bullet* bullet){
    if(bullet->x >= (enemy->x - 75) && bullet->x <= (enemy->x + 45) && bullet->y >= (enemy->y - 20)&& bullet->y <= (enemy->y + 40) && enemy->isAlive == true && bullet->isActive == true){
        bullet->isActive = false;
        enemy->health -= 50;
        if(enemy->health <= 0){
            enemy->frame = 0;
        }
        bullet->frame = 0;
    }
    else if(enemy->health <= 0){
        enemy->isAlive = false;
    }
    if(player->isAlive == false){
        player->isHit == false;
    }
    if(player->x >= (enemy->x - 65) && player->x <= (enemy->x + 65) && player->y >= (enemy->y - 90)&& player->y <= (enemy->y + 40) && enemy->isAlive == true && player->isHit == false && player->isAlive == true){
        if(enemy->frame = 6){
            player->health -= 10;
            player->isHit = true;
            player->frame = 0;
        }
        if(player->health <= 0){
            player->isAlive = false;
            player->frame = 0;
        }
        enemy->isAttacking = true;
    }
    else if (player->x < enemy->x - 65 || player->x > enemy->x + 65 || player->y < enemy->y - 90 || player->y > enemy->y + 40 || enemy->isAlive != true || player->isAlive != true){
        enemy->isAttacking = false;
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
