#include "entity_textures.h"

playerTexture textureLoad(SDL_Renderer* renderer, bool dead, bool moving, int width, int height, direction dir){
    if(dead == true){
        SDL_Surface* surface = SDL_LoadBMP("C:/vsjobs/game-main/pictures/Wanderer Magican/Dead.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return (playerTexture){texture, (SDL_Rect){50, 50, width, height}, (SDL_Rect){50, 50, width, height}, false, false, dir};
    }
    if(moving == true){
        SDL_Surface* surface = SDL_LoadBMP("C:/vsjobs/game-main/pictures/Wanderer Magican/Walk.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return (playerTexture){texture, (SDL_Rect){50, 50, width, height}, (SDL_Rect){50, 50, width, height}, true, true, dir};
    }
    else {
        SDL_Surface* surface = SDL_LoadBMP("C:/vsjobs/game-main/pictures/Wanderer Magican/Idle.png");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return (playerTexture){texture, (SDL_Rect){50, 50, width, height}, (SDL_Rect){50, 50, width, height}, true, false, dir};
    }
}