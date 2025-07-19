#include <iostream>
#include <cmath>
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
    SDL_Texture* snakeTexture = IMG_LoadTexture(renderer, "../assets/snake.png");
    SDL_GetTextureSize(mapTexture, &mapWidth, &mapHeight);

    SDL_FRect viewport {mapWidth/2, mapHeight/2, screenWidth, screenHeight};
    SDL_FRect snake {mapWidth/2, mapHeight/2, 0.0f, 0.0f};
    SDL_GetTextureSize(snakeTexture, &snake.w, &snake.h);
    SDL_FRect snakeViewport {snake.x - viewport.x, snake.y - viewport.y, snake.w, snake.h};
    
    SDL_Event event;
    bool running = true;

    Uint64 lastTime = SDL_GetTicks();
    while (running) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1.0e3f; // Convert to seconds
        lastTime = currentTime;

        float currentZoomFactor;
        const bool* keys = SDL_GetKeyboardState(nullptr);
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
                case SDL_EVENT_MOUSE_WHEEL:
                    // Adjust viewport size based on mouse wheel scroll
                    float viewportChangeX = event.wheel.y * zoomSpeed * deltaTime;
                    float viewportChangeY = viewportChangeX * aspectRatio;
                    float newOldRatio = viewport.w / (viewport.w + viewportChangeX);

                    viewport.w += viewportChangeX;
                    viewport.h += viewportChangeY;
                    viewport.x -= viewportChangeX / 2;
                    viewport.y -= viewportChangeY / 2;

                    snakeViewport.w *= newOldRatio;
                    snakeViewport.h *= newOldRatio;

                    if (viewport.h < 500) {
                        viewport.x -= (500 / aspectRatio - viewport.w) / 2;
                        viewport.y -= (500 - viewport.h) / 2;
                        viewport.h = 500;
                        viewport.w = 500 / aspectRatio;
                        snakeViewport.w /= newOldRatio;
                        snakeViewport.h /= newOldRatio;
                    }
                    else if (viewport.h > mapHeight) {
                        viewport.x -= (mapHeight / aspectRatio - viewport.w) / 2;
                        viewport.y -= (mapHeight - viewport.h) / 2;
                        viewport.h = mapHeight;
                        viewport.w = mapHeight / aspectRatio;
                        snakeViewport.w /= newOldRatio;
                        snakeViewport.h /= newOldRatio;
                    }
                    else if (viewport.w > mapWidth) {
                        viewport.x -= (mapWidth * aspectRatio - viewport.w) / 2; // Not sure about *
                        viewport.y -= (mapWidth - viewport.h) / 2;
                        viewport.w = mapWidth;
                        viewport.h = mapWidth * aspectRatio;
                        snakeViewport.w /= newOldRatio; // Not sure about /
                        snakeViewport.h /= newOldRatio;
                    }

                    if (viewport.x < 0) viewport.x = 0;
                    else if (viewport.x + viewport.w > mapWidth) viewport.x = mapWidth - viewport.w;
                    if (viewport.y < 0) viewport.y = 0;
                    else if (viewport.y + viewport.h > mapHeight) viewport.y = mapHeight - viewport.h;
                    break;
            }

            float dx{0.0f};
            float dy{0.0f};
            float length{0.0f};
            
            if (keys[SDL_SCANCODE_W]) dy -= 1.0f;
            if (keys[SDL_SCANCODE_S]) dy += 1.0f;
            if (keys[SDL_SCANCODE_A]) dx -= 1.0f;
            if (keys[SDL_SCANCODE_D]) dx += 1.0f;
            length = std::sqrt(dx * dx + dy * dy);

            if (length > 0.0f) {
                if (dx != 0.0f) viewport.x += viewportSpeed * deltaTime * dx / length;
                if (dy != 0.0f) viewport.y += viewportSpeed * deltaTime * dy / length;
            }

            if (viewport.x < 0) viewport.x = 0;
            else if (viewport.x + viewport.w > mapWidth) viewport.x = mapWidth - viewport.w;
            if (viewport.y < 0) viewport.y = 0;
            else if (viewport.y + viewport.h > mapHeight) viewport.y = mapHeight - viewport.h;

            // Snake viewport position
            currentZoomFactor = screenWidth / viewport.w;

            snakeViewport.x = (snake.x - viewport.x) * currentZoomFactor;
            snakeViewport.y = (snake.y - viewport.y) * currentZoomFactor;

            // Snake movement
            if (keys[SDL_SCANCODE_Q]) snakeAngle -= (snakeAngle > -360.0f) ? snakeRotationSpeed * deltaTime: -360.0f;
            if (keys[SDL_SCANCODE_E]) snakeAngle += (snakeAngle < 360.0f) ? snakeRotationSpeed * deltaTime: -360.0f;
        }

        snake.x += snakeSpeed * deltaTime * std::cos(snakeAngle * M_PI / 180.0f);
        snake.y += snakeSpeed * deltaTime * std::sin(snakeAngle * M_PI / 180.0f);
        snakeViewport.x = (snake.x - viewport.x) * currentZoomFactor;
        snakeViewport.y = (snake.y - viewport.y) * currentZoomFactor;
        
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, mapTexture, &viewport, nullptr);
        SDL_RenderTextureRotated(renderer, snakeTexture, nullptr, &snakeViewport, snakeAngle, nullptr, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }
    
    // Clean up and exit
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
