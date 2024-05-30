#include "player.h"

Player* createPlayer(int x, int y, int width, int height, int health, int speed, int score){
    Player* player = (Player*)malloc(sizeof(Player));
    player->x = x;
    player->y = y;
    player->width = width;
    player->height = height;
    player->health = health;
    player->speed = speed;
    player->score = score;
    player->dir = RIGHT;
    player->isAlive = true;
    player->moving = false;
    player->isShooting = false;
    return player;
}

Bullet* createBullet(int x, int y, int width, int height, int speed, direction dir){
    Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
    bullet->x = x;
    bullet->y = y;
    bullet->width = width;
    bullet->height = height;
    bullet->speed = speed;
    bullet->dir = dir;
    bullet->isActive = false;
    bullet->hit = false;
    bullet->frame = 0;
    return bullet;
}

void movePlayer(Player* player, direction dir){
    if(dir == UP){
        player->y -= player->speed;
    }
    if(dir == DOWN){
        player->y += player->speed;
    }
    if(dir == LEFT){
        player->x -= player->speed;
    }
    if(dir == RIGHT){
        player->x += player->speed;
    }
}

void combatPlayer(Player* player, Bullet* bullet){
    bullet->isActive = true;
    bullet->dir = player->dir;
}
void updateBullet(Bullet* bullet, Player* player){
    if(bullet->isActive == true){
        if(bullet->dir == UP){
            bullet->y -= bullet->speed;
        }
        if(bullet->dir == DOWN){
            bullet->y += bullet->speed;
        }
        if(bullet->dir == LEFT){
            bullet->x -= bullet->speed;
        }
        if(bullet->dir == RIGHT){
            bullet->x += bullet->speed;
        }
        if(bullet->dir == UPRIGHT){
            bullet->x += bullet->speed;
            bullet->y -= bullet->speed;
        }
        if(bullet->dir == UPLEFT){
            bullet->x -= bullet->speed;
            bullet->y -= bullet->speed;
        }
        if(bullet->dir == DOWNRIGHT){
            bullet->x += bullet->speed;
            bullet->y += bullet->speed;
        }
        if(bullet->dir == DOWNLEFT){
            bullet->x -= bullet->speed;
            bullet->y += bullet->speed;
        }
    }
    if(bullet->x < 0 || bullet->x >= 10000 || bullet->y < 0 || bullet->y >= 70000){
        bullet->isActive = false;
        bullet->hit = true;
    }
    if(bullet->isActive == false){
        bullet->x = player->x;
        bullet->y = player->y;
    }
}

void updatePlayer(Player* player){
    if(player->health <= 0){
        player->isAlive = false;
    }
    
}

void destroyPlayer(Player* player){
    free(player);
}