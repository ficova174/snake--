#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "constants.h"

int main(int argc, char* argv[]) {
    // Initialize SDL
    SDL_SetAppMetadata("Snake++", nullptr, nullptr);
    SDL_SetAppMetadataProperty(SDL_PROP_APP_METADATA_CREATOR_STRING, "Axel L.");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %u", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Snake++", screenWidth, screenHeight, 0, &window, &renderer)) {
        SDL_Log("SDL_CreateWindowAndRenderer failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Texture* mapTexture = IMG_LoadTexture(renderer, "../assets/map.png");

    float mapWidth = 0.0f;
    float mapHeight = 0.0f;
    SDL_GetTextureSize(mapTexture, &mapWidth, &mapHeight);

    SDL_FRect viewport {mapWidth/2, mapHeight/2, screenWidth, screenHeight};

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.scancode) {
                        case SDL_SCANCODE_W:
                            viewport.y -= viewportSpeed;
                            break;
                        case SDL_SCANCODE_S:
                            viewport.y += viewportSpeed;
                            break;
                        case SDL_SCANCODE_A:
                            viewport.x -= viewportSpeed;
                            break;
                        case SDL_SCANCODE_D:
                            viewport.x += viewportSpeed;
                            break;
                    }
                    break;
                case SDL_EVENT_MOUSE_WHEEL:
                    // Adjust viewport size based on mouse wheel scroll
                    float viewportChangeX = event.wheel.y * zoomSpeed;
                    float viewportChangeY = event.wheel.y * zoomSpeed * aspectRatio;
                    viewport.w += viewportChangeX;
                    viewport.h += viewportChangeY;
                    viewport.x -= viewportChangeX/2;
                    viewport.y -= viewportChangeY/2;
                    break;
            }

            // Clamp viewport size
            if (viewport.w < 100) viewport.w = 100;
            if (viewport.h < 100) viewport.h = 100;
            if (viewport.w > mapWidth) viewport.w = mapWidth;
            if (viewport.h > mapHeight) viewport.h = mapHeight;

            // Clamp position
            if (viewport.x < 0) viewport.x = 0;
            if (viewport.y < 0) viewport.y = 0;
            if (viewport.x + viewport.w > mapWidth) viewport.x = mapWidth - viewport.w;
            if (viewport.y + viewport.h > mapHeight) viewport.y = mapHeight - viewport.h;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, mapTexture, &viewport, nullptr);
        SDL_RenderPresent(renderer);
    }
    
    // Clean up and exit
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
