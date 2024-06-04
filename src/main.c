#define SDL_MAIN_HANDLED
#include "enemy.h"
#include <SDL_image.h>



int main(){
    Uint32 startTime = SDL_GetTicks();
    int x = 0;
    int Xsize = 1500;
    int Ysize = 700;

    SDL_Texture *bulletTexture = NULL;
    SDL_Texture *backgroundTexture = NULL;

    Player* player = createPlayer(100, 100, 200, 200, 100, 3, 0);
    
    Bullet* bullet = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet2 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet3 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet4 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet5 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullets[5] = {bullet, bullet2, bullet3, bullet4, bullet5};

    skeleton* skeleton1 = createSkeleton(1000, 100, 200, 200, 100, 2);
    skeleton* skeleton2 = createSkeleton(1000, 200, 200, 200, 100, 2);
    skeleton* skeleton3 = createSkeleton(1000, 300, 200, 200, 100, 2);
    goblin* goblin1 = createGoblin(400, 100, 200, 200, 50, 5);
    goblin* goblin2 = createGoblin(500, 100, 200, 200, 50, 5);
    goblin* goblin3 = createGoblin(600, 100, 200, 200, 50, 5);

    skeleton* skeletons[3] = {skeleton1, skeleton2, skeleton3};
    goblin* goblins[3] = {goblin1, goblin2, goblin3};

    Boss* boss = createBoss(1000, 100, 200, 200, 2);
    
    SDL_Rect goblinsRect[3];
    SDL_Rect skeletonsRect[3];


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
    player->walk = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Walk.png");
    player->idle = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Idle.png");
    player->attack = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Attack_1.png");
    player->dead = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Dead.png");
    player->hit = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Hurt.png");

    for(int i = 0; i<3; i++){
        skeletons[i]->walk = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Skeleton/Walk.png");
        skeletons[i]->idle = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Skeleton/Idle.png");
        skeletons[i]->attack = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Skeleton/Attack.png");
        skeletons[i]->dead = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Skeleton/Death.png");
        skeletons[i]->hit = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Skeleton/Take Hit.png");

        goblins[i]->walk = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Goblin/Run.png");
        goblins[i]->idle = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Goblin/Idle.png");
        goblins[i]->attack = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Goblin/Attack.png");
        goblins[i]->dead = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Goblin/Death.png");
        goblins[i]->hit = IMG_LoadTexture(renderer, "pictures/Monsters_Creatures_Fantasy/Goblin/Take Hit.png");
    }
    bulletTexture = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Charge_2.png");

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
    if(player->isShooting == false){
        if(state[SDL_SCANCODE_W]){
            player->moving = true;
            movePlayer(player, UP);
            player->dir = UP;
        }
        if(state[SDL_SCANCODE_S]){
            player->moving = true;
            movePlayer(player, DOWN);
            player->dir = DOWN;
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
        if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]){
            player->dir = UPLEFT;
        }
        if(state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]){
            player->dir = UPRIGHT;
        }
        if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A]){
            player->dir = DOWNLEFT;
        }
        if(state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D]){
            player->dir = DOWNRIGHT;
        }
        if(!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S] && !state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]){
            player->moving = false;
        }
    }

    for(int i = 0; i < 5; i++){
        updateBullet(bullets[i], player);
        bulletRect[i].x = bullets[i]->x;
        bulletRect[i].y = bullets[i]->y;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //player texture render

    SDL_Rect playerRect = {player->x, player->y, player->width, player->height};
    if(player->dir == RIGHT || player->dir == UPRIGHT || player->dir == DOWNRIGHT || player->dir == UP || player->dir == DOWN){
        if(player->moving == false && player->isShooting == false){
            SDL_RenderCopyEx(renderer, player->idle, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
        if(player->moving == true && player->isShooting == false){
            SDL_RenderCopyEx(renderer, player->walk, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
        if(player->isShooting == true){
            SDL_RenderCopyEx(renderer, player->attack, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
    }
    else if(player->dir == LEFT || player->dir == UPLEFT || player->dir == DOWNLEFT || player->dir == UP || player->dir == DOWN){
        if(player->moving == false && player->isShooting == false){
            SDL_RenderCopyEx(renderer, player->idle, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
        if(player->moving == true && player->isShooting == false){
            SDL_RenderCopyEx(renderer, player->walk, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
        if(player->isShooting == true){
            SDL_RenderCopyEx(renderer, player->attack, &(SDL_Rect) {x*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
    }

    currentTime = SDL_GetTicks();
    if(currentTime - startTime >= 100){
        startTime = currentTime;
        x++;
        for(int i = 0; i < 5; i++){
            bullets[i]->frame++;
            if(i < 3){
                goblins[i]->frame++;
                skeletons[i]->frame++;
            }
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


    //bullet texture render

    for(int i = 0; i < 5; i++){
        if(bullets[i]->dir == RIGHT || bullets[i]->dir == LEFT){
            bullets[i]->angle = 0;
        }
        else if(bullets[i]->dir == DOWNRIGHT || bullets[i]->dir == UPLEFT){
            bullets[i]->angle = 45;
        }
        else if(bullets[i]->dir == UPRIGHT || bullets[i]->dir == DOWNLEFT){
            bullets[i]->angle = -45;
        }
        else if(bullets[i]->dir == UP || bullets[i]->dir == DOWN){
            bullets[i]->angle = 90;
        }
        if(bullets[i]->isActive == true){
            SDL_RenderCopyEx(renderer, bulletTexture, &(SDL_Rect) {bullets[i]->frame*64, 0, 64, 128}, &bulletRect[i], bullets[i]->angle , NULL, 0);
        }
        if(bullets[i]->frame>5){
            bullets[i]->frame = 0;
        }
    }
    //load enemy textures
    
    for(int i = 0; i < 3; i++){
        // moveSkeleton(skeletons[i]);
        // moveGoblin(goblins[i]);

        skeletonsRect[i] = (SDL_Rect){skeletons[i]->x, skeletons[i]->y, skeletons[i]->width, skeletons[i]->height};
        goblinsRect[i] = (SDL_Rect){goblins[i]->x, goblins[i]->y, goblins[i]->width, goblins[i]->height};
        //goblin texture render
        if(goblins[i]->isAlive == true && goblins[i]->moving == true){
            if(goblins[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (goblins[i]->walk), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 1);
            }
            else if(goblins[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (goblins[i]->walk), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 0);
            }
            if(goblins[i]->frame>7){
                goblins[i]->frame = 0;
            }
        }
        else if(goblins[i]->isAlive == true && goblins[i]->moving == false){
            if(goblins[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (goblins[i]->idle), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 1);
            }
            else if(goblins[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (goblins[i]->idle), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 0);
            }
            if(goblins[i]->frame>2){
                goblins[i]->frame = 0;
            }
        }
        else if(goblins[i]->isAlive == false){
            if(goblins[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (goblins[i]->dead), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 1);
            }
            else if(goblins[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (goblins[i]->dead), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 0);
            }
        }
        //skeleton texture render
        if(skeletons[i]->isAlive == true && skeletons[i]->moving == true){
            if(skeletons[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->walk), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 1);
            }
            else if(skeletons[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->walk), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 0);
            }
            if(skeletons[i]->frame>2){
                skeletons[i]->frame = 0;
            }
        }
        else if(skeletons[i]->isAlive == true && skeletons[i]->moving == false){
            if(skeletons[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->idle), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 1);
            }
            else if(skeletons[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->idle), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 0);
            }
            if(skeletons[i]->frame>2){
                skeletons[i]->frame = 0;
            }
        }
        else if(skeletons[i]->isAlive == false){
            if(skeletons[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->dead), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 1);
            }
            else if(skeletons[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->dead), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 0);
            }
        }
    }
    int bc = 0;
    for(int e = 0; e < 3;){
        skeletonCombat(skeletons[e], player, bullets[bc]);
        goblinCombat(goblins[e], player, bullets[bc]);
        bc++;
        if(bc >= 4){
            bc = 0;
            e++;
        }
    }

    SDL_RenderPresent(renderer);
    }
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}