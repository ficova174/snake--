#include "game.h"
#include "constants.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* mapTexture;
SDL_Texture* snakeTexture;

bool gameInit() {
    SDL_SetAppMetadata("Snake++", nullptr, nullptr);
    SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, "Axel L.");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %u", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (!SDL_CreateWindowAndRenderer("Snake++", screenWidth, screenHeight, 0, &window, &renderer)) {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    mapTexture = IMG_LoadTexture(renderer, "../assets/map.png");
    snakeTexture = IMG_LoadTexture(renderer, "../assets/snake.png");
    
    if (!mapTexture) {
        SDL_Log("Failed to load map texture: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!snakeTexture) {
        SDL_Log("Failed to load snake texture: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    return 0;
}

void gameLoop() {

}

void gameCleanup() {
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(snakeTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}