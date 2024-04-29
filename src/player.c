#include "./player.h"

Player playerCreate(int x, int y, int width, int height, int speed, int health, int score){
    Player player;
    player.x = x;
    player.y = y;
    player.width = width;
    player.height = height;
    player.rect = (SDL_Rect){x, y, width, height};
    player.speed = speed;
    player.health = health;
    player.score = score;
    player.active = true;
    player.moving = false;
    return player;
}

void playerMove(Player* player, const Uint8* state, int playerspeed){
    if (state[SDL_SCANCODE_W]) {
        player->y -= player->speed;
        player -> dir = UP;
        player -> moving = true;
    }
    if (state[SDL_SCANCODE_S]) {
        player->y += player->speed;
        player -> dir = DOWN;
        player -> moving = true;
    }
    if (state[SDL_SCANCODE_A]) {
        player->x -= player->speed;
        player -> dir = LEFT;
        player -> moving = true;
    }
    if (state[SDL_SCANCODE_D]) {
        player->x += player->speed;
        player -> dir = RIGHT;
        player -> moving = true;
    }
        if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) {
        player -> dir = UPLEFT;
    }
    if(state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W]) {
        player -> dir = UPRIGHT;
    }
    if(state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S]) {
        player -> dir = DOWNLEFT;
    }
    if(state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S]) {
        player->dir = DOWNRIGHT;
    }
    else {
        player -> moving = false;
    }
    player->rect.x = player->x;
    player->rect.y = player->y;
}
