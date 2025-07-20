#pragma once
#include <SDL3/SDL.h>

bool gameInit();
void gameLoop();
void gameCleanup();

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* mapTexture = nullptr;
SDL_Texture* snakeTexture = nullptr;
