#include "bullet.h"

Bullet bulletCreate(int x, int y, int width, int height, int speed) {
    Bullet bullet;

    bullet.x = x;
    bullet.y = y;
    bullet.width = width;
    bullet.height = height;
    bullet.rect = (SDL_Rect) {x, y, width, height};
    bullet.speed = speed;
    bullet.active = false;

    return bullet;
}

void bulletDirection(Bullet* bullet, direction dir, const Uint8* state) {
    bullet -> active = true;
    if(state[SDL_SCANCODE_W] || dir == UP) {
        bullet->dir = UP;
    }
    if(state[SDL_SCANCODE_S] || dir == DOWN) {
        bullet -> dir = DOWN;
    }
    if(state[SDL_SCANCODE_A] || dir == LEFT) {
        bullet -> dir = LEFT;
    }
    if(state[SDL_SCANCODE_D] || dir == RIGHT){
        bullet -> dir = RIGHT;
    }
    if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A] || dir == UPLEFT) {
        bullet -> dir = UPLEFT;
    }
    if(state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W] || dir == UPRIGHT) {
        bullet -> dir = UPRIGHT;
    }
    if(state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S] || dir == DOWNLEFT) {
        bullet -> dir = DOWNLEFT;
    }
    if(state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S] || dir == DOWNRIGHT) {
        bullet -> dir = DOWNRIGHT;
    }
}

void bulletMove(Bullet* bullet, direction dir, int playerX, int playerY) {
    if (bullet->active == true) {
        if (bullet->dir == UP) {
            bullet->y -= bullet->speed;
            bullet->rect.y = bullet->y;
        }
        if (bullet->dir == DOWN) {
            bullet->y += bullet->speed;
            bullet->rect.y = bullet->y;
        }
        if (bullet->dir == LEFT) {
            bullet->x -= bullet->speed;
            bullet->rect.x = bullet->x;

        }
        if (bullet->dir == RIGHT) {
            bullet->x += bullet->speed;
            bullet->rect.x = bullet->x;
        }
        if(bullet->dir == UPLEFT) {
            bullet->x -= bullet->speed;
            bullet->y -= bullet->speed;
            bullet->rect.x = (bullet->x-=2);
            bullet->rect.y = (bullet->y-=2);
        }
        if(bullet->dir == UPRIGHT) {
            bullet->x += bullet->speed;
            bullet->y -= bullet->speed;
            bullet->rect.x = (bullet->x-=2);
            bullet->rect.y = (bullet->y-=2);
        }
        if(bullet->dir == DOWNLEFT) {
            bullet->x -= bullet->speed;
            bullet->y += bullet->speed;
            bullet->rect.x = (bullet->x-=2);
            bullet->rect.y = (bullet->y-=2);
        }
        if(bullet->dir == DOWNRIGHT){
            bullet->x += bullet->speed;
            bullet->y += bullet->speed;
            bullet->rect.x = (bullet->x-=2);
            bullet->rect.y = (bullet->y-=2);
        }
    }
    if(bullet->x <= 0 || bullet->x >= 990 || bullet->y <= 0 || bullet->y >= 690){
        bullet->active = false;
    }
    if(bullet->active == false){
        bullet->x = playerX;
        bullet->y = playerY;
        bullet->rect.x = playerX + 20;
        bullet->rect.y = playerY + 20;
    }
}