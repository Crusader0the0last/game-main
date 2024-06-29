#define SDL_MAIN_HANDLED

#include "enemy.h"
#include <SDL_image.h>



int main(){
    Uint32 startTime = SDL_GetTicks();
    int Xsize = 1500;
    int Ysize = 700;
    SDL_Texture *bulletTexture = NULL;

    //vytvareni objektu hrace a brany
    Totem* totem = createtotem(100, 200, 200, 200, 100);
    Player* player = createPlayer(100, 100, 200, 200, 100, 3, 0);
    
    //vytvareni objektu streli hrace
    Bullet* bullet = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet2 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet3 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet4 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullet5 = createBullet(100, 100, 200, 200, 20, RIGHT);
    Bullet* bullets[5] = {bullet, bullet2, bullet3, bullet4, bullet5};


    //vytvareni objektu skeleton a goblin(nepratele)
    skeleton* skeleton1 = createSkeleton(2800, 100, 200, 200, 100, 2);
    skeleton* skeleton2 = createSkeleton(2400, 200, 200, 200, 100, 2);
    skeleton* skeleton3 = createSkeleton(2700, 300, 200, 200, 100, 2);
    goblin* goblin1 = createGoblin(1200, 100, 200, 200, 50, 3);
    goblin* goblin2 = createGoblin(1000, 300, 200, 200, 50, 3);
    goblin* goblin3 = createGoblin(1100, 500, 200, 200, 50, 3);

    //ukazatel na objekty
    skeleton* skeletons[3] = {skeleton1, skeleton2, skeleton3};
    goblin* goblins[3] = {goblin1, goblin2, goblin3};

    //vytvareni objektu boss
    Boss* boss = createBoss(1000, 100, 200, 200, 2);
    
    SDL_Rect goblinsRect[3];
    SDL_Rect skeletonsRect[3];


    SDL_Rect bulletRect[5];
    for(int i = 0; i < 5; i++){
        bulletRect[i] = (SDL_Rect){bullets[i]->x, bullets[i]->y, bullets[i]->width, bullets[i]->height};
    }
    
       //tvorba okna
    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Xsize, Ysize, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    //tvorba rendereru
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //pridelovani textur do entit a objektu
    player->walk = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Walk.png");
    player->idle = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Idle.png");
    player->attack = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Attack_1.png");
    player->dead = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Dead.png");
    player->hit = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Hurt.png");
    player->jump = IMG_LoadTexture(renderer, "pictures/Wanderer Magican/Jump.png");

    totem->main = IMG_LoadTexture(renderer, "pictures/FlyingObelisk_no_lightnings_no_letter.png");
    totem->death = IMG_LoadTexture(renderer, "pictures/Holy VFX 02/Holy VFX 02.png");

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

    //doplnek k casovani frames
    Uint32 currentTime = 0;

    //polovina setupu "state" pro pohyb a akce hrace
    const Uint8* state = SDL_GetKeyboardState(NULL);

    //hlavni loop
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
    //pozadi na cerno
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //druha polovina state
    state = SDL_GetKeyboardState(NULL);

    //utok hrace
    static bool isFKeyPressed = false;
        if(state[SDL_SCANCODE_F] && !isFKeyPressed && player->isShooting == false && player->isHit == false){
            isFKeyPressed = true;
            for(int i = 0; i < 5; i++){
                if(bullets[i]->isActive == false) {
                    player->frame = 0;
                    player->isShooting = true;
                    combatPlayer(player, bullets[i]);
                    break;
                }
            }
        }
    if(state[SDL_SCANCODE_F]){
        isFKeyPressed = false;
    }

    //pohyb hrace
    if(player->isShooting == false && player->isAlive == true){
        if(state[SDL_SCANCODE_W]){
            player->moving = true;
            playerJump(player);
            player->dir = UP;
        }
        if(state[SDL_SCANCODE_S]){
            // player->moving = true;
            // movePlayer(player, DOWN);
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

    //pohyb a update strel
    for(int i = 0; i < 5; i++){
        updateBullet(bullets[i], player);
        bulletRect[i].x = bullets[i]->x;
        bulletRect[i].y = bullets[i]->y;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //render hrace
    SDL_Rect playerRect = {player->x, player->y, player->width, player->height};
    if(player->dir == RIGHT || player->dir == UPRIGHT || player->dir == DOWNRIGHT || player->dir == UP || player->dir == DOWN){
        if(player->moving == false && player->isShooting == false && player->isAlive == true && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->idle, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
        else if(player->moving == true && player->isShooting == false && player->isAlive == true && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->walk, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
        else if(player->isShooting == true && player->isAlive == true && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->attack, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
        else if(player->isAlive == false && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->dead, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
        else if(player->isHit == true){
            if(player->frame == 3){
                player->isHit = false;
            }
            SDL_RenderCopyEx(renderer, player->hit, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 0);
        }
    }
    else if(player->dir == LEFT || player->dir == UPLEFT || player->dir == DOWNLEFT || player->dir == UP || player->dir == DOWN){
        if(player->moving == false && player->isShooting == false && player->isAlive == true && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->idle, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
        else if(player->moving == true && player->isShooting == false && player->isAlive == true && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->walk, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
        else if(player->isShooting == true && player->isAlive == true && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->attack, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
        else if(player->isAlive == false && player->isHit == false){
            SDL_RenderCopyEx(renderer, player->dead, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
        else if(player->isHit == true){
            if(player->frame == 3){
                    player->isHit = false;
            }
            SDL_RenderCopyEx(renderer, player->hit, &(SDL_Rect) {player->frame*128, 0, 128, 128}, &playerRect, 0, NULL, 1);
        }
    }

    //casovani hodnot pro kontrolu frames
    currentTime = SDL_GetTicks();
    if(currentTime - startTime >= 150 && player->isAlive == false){
        startTime = currentTime;
        if(player->frame < 3){
            player->frame++;
        }
        totem->frame++;
        for(int i = 0; i < 5; i++){
            bullets[i]->frame++;
            if(i < 3){
                goblins[i]->frame++;
                skeletons[i]->frame++;
            }
        }
    }
    else if(currentTime - startTime >= 100 && player->isAlive == true){
        startTime = currentTime;
        player->frame++;
        totem->frame++;
        for(int i = 0; i < 5; i++){
            bullets[i]->frame++;
            if(i < 3){
                goblins[i]->frame++;
                skeletons[i]->frame++;
            }
        }
    }
    if(player->frame > 7 && player->moving != true){
        player->frame = 0;
    }
    else if(player->frame > 6 && (player->moving == true || player->isShooting == true)){
        player->frame = 0;
        if(player->isShooting == true){
            player->isShooting = false;
        }
    }
    if(totem->frame > 11){
        totem->frame = 0;
        totem->isHit = false;
    }

    //render strel hrace
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

    //render nepratel (kostlivcu a goblinu zaroven)
    for(int i = 0; i < 3; i++){

        //pohyb nepratel
        moveSkeleton(skeletons[i]);
        moveGoblin(goblins[i]);

        skeletonsRect[i] = (SDL_Rect){skeletons[i]->x, skeletons[i]->y, skeletons[i]->width, skeletons[i]->height};
        goblinsRect[i] = (SDL_Rect){goblins[i]->x, goblins[i]->y, goblins[i]->width, goblins[i]->height};
        //goblin texture render
        if(goblins[i]->isAlive == true && goblins[i]->moving == true && goblins[i]->isAttacking == false){
            if(goblins[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (goblins[i]->walk), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 1);
            }
            else if(goblins[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (goblins[i]->walk), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 0);
            }
            if(goblins[i]->frame>6){
                goblins[i]->frame = 0;
            }
        }
        else if(goblins[i]->isAlive == true && goblins[i]->moving == false && goblins[i]->isAttacking == false){
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
        else if(goblins[i]->isAlive == false && goblins[i]->isAttacking == false){
            if(goblins[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (goblins[i]->dead), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 1);
            }
            else if(goblins[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (goblins[i]->dead), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 0);
            }
        }
        else if(goblins[i]->isAttacking == true && goblins[i]->isAlive == true){
            if(goblins[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (goblins[i]->attack), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 1);
            }
            else if(goblins[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (goblins[i]->attack), &(SDL_Rect) {goblins[i]->frame*150, 0, 150, 150}, &goblinsRect[i], 0, NULL, 0);
            }
            if(goblins[i]->frame > 6){
                goblins[i]->frame = 0;
            }
        }
        //kostlivci
        if(skeletons[i]->isAlive == true && skeletons[i]->moving == true && skeletons[i]->isAttacking == false){
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
        else if(skeletons[i]->isAlive == true && skeletons[i]->moving == false && skeletons[i]->isAttacking == false){
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
        else if(skeletons[i]->isAlive == false && skeletons[i]->isAttacking == false){
            if(skeletons[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->dead), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 1);
            }
            else if(skeletons[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->dead), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 0);
            }
        }
        else if(skeletons[i]->isAttacking == true && skeletons[i]->isAlive == true){
            if(skeletons[i]->dir == LEFT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->attack), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 1);
            }
            else if(skeletons[i]->dir == RIGHT){
                SDL_RenderCopyEx(renderer, (skeletons[i]->attack), &(SDL_Rect) {skeletons[i]->frame*150, 0, 150, 150}, &skeletonsRect[i], 0, NULL, 0);
            }
            if(skeletons[i]->frame > 6){
                skeletons[i]->frame = 0;
            }
        }
    }

    //combat nepratel (urcovani jejich utoku a jejich umirani)
    int bc = 0;
    for(int e = 0; e < 3;){
        skeletonCombat(skeletons[e], player, bullets[bc], totem);
        goblinCombat(goblins[e], player, bullets[bc]);
        bc++;
        if(bc >= 4){
            bc = 0;
            e++;
        }
    }

    //render totemu(portalu)
    SDL_RenderCopyEx(renderer, totem->main, &(SDL_Rect) {totem->frame*200, 0, 400, 400}, &(SDL_Rect) {totem->x, totem->y, totem->width, totem->height}, 0, NULL, 0);
    for(int i =0; i<3; i++){
        if(totem->isAlive == false){
            SDL_RenderCopyEx(renderer, totem->death, &(SDL_Rect) {totem->frame*51, 0, 48, 48}, &(SDL_Rect) {totem->x, totem->y, totem->width, totem->height}, 0, NULL, 0);
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