#pragma once
#include <SDL3/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* mapTexture;
extern SDL_Texture* snakeTexture;

bool gameInit();
void gameLoop();
void gameCleanup();
