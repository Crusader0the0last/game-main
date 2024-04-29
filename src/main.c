#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include "bullet.h"
#include "enemy.h"
#include "player.h"


int main() {
    printf("Hello, SDL!\n");
    int picture = 0;
    Player player = playerCreate(0, 0, 50, 50, 3, 100, 0);


    //creating projectiles
    Bullet bullet1 = bulletCreate(0, 0, 10, 10, 10);
    Bullet bullet2 = bulletCreate(0, 0, 10, 10, 10);
    Bullet bullet3 = bulletCreate(0, 0, 10, 10, 10);
    Bullet bullet4 = bulletCreate(0, 0, 10, 10, 10);
    Bullet bullet5 = bulletCreate(0, 0, 10, 10, 10);
    Bullet bullets[5] = {bullet1, bullet2, bullet3, bullet4, bullet5};
    
    // creating entities
    Enemy enemyPetr1 = enemyCreate(0, 0, 50, 50, ENEMY1, 2, 30);
    Enemy enemyPetr2 = enemyCreate(0, 0, 50, 50, ENEMY1, 2, 30);
    Enemy enemyPetr3 = enemyCreate(0, 0, 50, 50, ENEMY1, 2, 30);
    Enemy enemyPetr4 = enemyCreate(0, 0, 50, 50, ENEMY1, 2, 30);
    Enemy enemySwiftTwin1 = enemyCreate(0, 0, 30, 30, ENEMY2, 4, 15);
    Enemy enemySwiftTwin2 = enemyCreate(0, 0, 30, 30, ENEMY2, 4, 15);
    Enemy enemySummoner = enemyCreate(0, 0, 30, 30, ENEMY3, 1, 30);
    Enemy Boss = enemyCreate(0, 0, 80, 80, ENEMY4, 2, 100);
    Enemy summonedOne1 = enemyCreate(0, 0, 55, 55, ENEMY5, 2, 40);
    Enemy summonedOne2 = enemyCreate(0, 0, 55, 55, ENEMY5, 2, 40);
    Enemy summonedOne3 = enemyCreate(0, 0, 55, 55, ENEMY5, 2, 40);

    //grouping same enemy types
    Enemy Petove[4] = {enemyPetr1, enemyPetr2, enemyPetr3, enemyPetr4};
    Enemy SwiftTwins[2] = {enemySwiftTwin1, enemySwiftTwin2};
    Enemy SummonedOnes[3] = {summonedOne1, summonedOne2, summonedOne3};
    
    const int Ysize = 700;
    const int Xsize = 1000;
    int playerspeed = 3;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
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

        // Set render color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &player.rect);
        const Uint8* state = SDL_GetKeyboardState(NULL);
        enum direction {UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT};
        direction dir = RIGHT;
        playerMove(&player, state, playerspeed);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for(int e = 0; e < 4; e++){
            SDL_RenderFillRect(renderer, &Petove[e].rect);
            enemyMove(&Petove[e], bullets[e].x, bullets[e].y);
        }
    SDL_Texture* playerTexture = NULL;
    SDL_Surface* playerSurface = SDL_LoadBMP("assets/player.bmp");
    if(playerSurface == NULL){
        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
        return 1;
    }
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerSurface);

        //player combat
        static bool isFKeyPressed = false;
        if(state[SDL_SCANCODE_F] && !isFKeyPressed){
            isFKeyPressed = true;
            //if(bullet1active == true && bullet2active == true && bullet3active == true && bullet4active == true && bullet5active == true){
            //sdl2_ttf::messageBox("no mana");
            //}
            for(int i = 0; i < 5; i++){
                if(bullets[i].active == false) {
                    bulletDirection(&bullets[i], &player);
                    break;
                }
            }
        }
        picture++;
        SDL_RenderCopy(renderer, playerTexture, picture, &player.rect);
        
        if(!state[SDL_SCANCODE_F]){
            isFKeyPressed = false;
        }
        for(int i = 0; i < 5; i++){
            bulletMove(&bullets[i], bullets[i].dir, player.x, player.y);
        }
        

        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &bullets[0].rect);
        SDL_RenderFillRect(renderer, &bullets[1].rect);
        SDL_RenderFillRect(renderer, &bullets[2].rect);
        SDL_RenderFillRect(renderer, &bullets[3].rect);
        SDL_RenderFillRect(renderer, &bullets[4].rect);
        
        
        // Update the screen
        SDL_RenderPresent(renderer); 
    }
    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}