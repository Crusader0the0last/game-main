#define SDL_MAIN_HANDLED
#include "enemy.h"
#include <SDL_image.h>



int main(){
    Uint32 startTime = SDL_GetTicks();
    int x = 0;
    int Xsize = 1000;
    int Ysize = 700;

    SDL_Texture *enemyTexture = NULL;
    SDL_Texture *playerTexture = NULL;
    SDL_Texture *bulletTexture = NULL;
    SDL_Texture *backgroundTexture = NULL;

    Player* player = createPlayer(100, 100, 200, 200, 100, 3, 0);
    
    Bullet* bullet = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet2 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet3 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet4 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet5 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullets[5] = {bullet, bullet2, bullet3, bullet4, bullet5};

    Enemy* enemy1 = createSimpleEnemy(500, 0, 200, 200, 100, 2);
    Enemy* enemy2 = createSimpleEnemy(500, 200, 200, 200, 100, 2);
    Enemy* enemy3 = createSimpleEnemy(500, 300, 200, 200, 100, 2);
    Enemy* enemy4 = createSimpleEnemy(100, 100, 200, 200, 50, 5);
    Enemy* enemy5 = createSimpleEnemy(100, 100, 200, 200, 50, 5);
    Enemy* enemy6 = createSimpleEnemy(100, 100, 200, 200, 70, 3);

    Enemy* enemies[6] = {enemy1, enemy2, enemy3, enemy4, enemy5, enemy6};
    SDL_Rect enemyRect[6];


    SDL_Rect bulletRect[5];
    for(int i = 0; i < 5; i++){
        bulletRect[i] = (SDL_Rect){bullets[i]->x, bullets[i]->y, bullets[i]->width, bullets[i]->height};
    }
    
       // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Xsize, Ysize, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    Uint32 currentTime = 0;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }
        }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_W]){
        player->moving = true;
        movePlayer(player, UP);
    }
    if(state[SDL_SCANCODE_S]){
        player->moving = true;
        movePlayer(player, DOWN);
    }
    if(state[SDL_SCANCODE_A]){
        player->moving = true;
        movePlayer(player, LEFT);
        player->dir = LEFT;
    }
    if(state[SDL_SCANCODE_D]){
        player->moving = true;
        movePlayer(player, RIGHT);
        player->dir = RIGHT;
    }
    if(!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]){
        player->moving = false;
    }

    static bool isFKeyPressed = false;
        if(state[SDL_SCANCODE_F] && !isFKeyPressed && player->isShooting == false){
            isFKeyPressed = true;
            //if(bullet1active == true && bullet2active == true && bullet3active == true && bullet4active == true && bullet5active == true){
            //sdl2_ttf::messageBox("no mana");
            //}
            for(int i = 0; i < 5; i++){
                if(bullets[i]->isActive == false) {
                    x = 0;
                    player->isShooting = true;
                    combatPlayer(player, bullets[i]);
                    break;
                }
            }
        }
    if(state[SDL_SCANCODE_F]){
        isFKeyPressed = false;
    }

    for(int i = 0; i < 5; i++){
        updateBullet(bullets[i], player);
        bulletRect[i].x = bullets[i]->x;
        bulletRect[i].y = bullets[i]->y;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //player texture render


    if(player->moving == false && player->isShooting == false){
        playerTexture = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Idle.png");
    }
    if(player->moving == true && player->isShooting == false){
        playerTexture = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Walk.png");
    }
    if(player->isShooting == true){
        playerTexture = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Attack_1.png");
    }
    bulletTexture = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Charge_2.png");

    currentTime = SDL_GetTicks();
    if(currentTime - startTime >= 100){
        startTime = currentTime;
        x++;
        enemy1->frame++;
        for(int i = 0; i < 5; i++){
            bullets[i]->frame++;
        }
    }
    if(x>7 && player->moving != true){
        x = 0;
    }
    if(x>6 && (player->moving == true || player->isShooting == true)){
        x = 0;
        if(player->isShooting == true){
            player->isShooting = false;
        }
    }
    //rendering player

    SDL_Rect playerRect = {player->x, player->y, player->width, player->height};

    if(player->dir == RIGHT){
        SDL_RenderCopyEx(renderer, playerTexture, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
    }
    else if(player->dir == LEFT){
        SDL_RenderCopyEx(renderer, playerTexture, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
    }



    //bullet texture render

    for(int i = 0; i < 5; i++){
        if(bullets[i]->isActive == true){
            if(bullets[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, bulletTexture, &(SDL_Rect) {bullets[i]->frame*64, 0, 64, 128}, &bulletRect[i], 0 , NULL, 0);
            }
            else if(bullets[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, bulletTexture, &(SDL_Rect) {bullets[i]->frame*64, 0, 64, 128}, &bulletRect[i], 0 , NULL, 1);
        }
    }
    if(bullets[i]->frame>5){
        bullets[i]->frame = 0;
    }
    }
    //render enemies
    enemyTexture = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Skeleton/Walk.png");
    for(int i = 0; i < 6; i++){
        if(enemies[i]->isAlive == true && i < 3){
            
        }
        enemyRect[i] = (SDL_Rect){enemies[i]->x, enemies[i]->y, enemies[i]->width, enemies[i]->height};

        if(enemies[i]->dir == LEFT){
            SDL_RenderCopyEx(renderer, enemyTexture, &(SDL_Rect) {enemies[i]->frame*150, 0, 150, 150}, &enemyRect[i], 0, NULL, 1);
        }
        else if(enemies[i]->dir == RIGHT){
            SDL_RenderCopyEx(renderer, enemyTexture, &(SDL_Rect) {enemies[i]->frame*150, 0, 150, 150}, &enemyRect[i], 0, NULL, 0);
        }
        if(enemies[i]->frame>2){
            enemies[i]->frame = 0;
        }
        moveEnemy(enemies[i]);

    }

    SDL_RenderPresent(renderer);
    }
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}