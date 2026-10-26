#pragma once 

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "chip8.h"

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define WINDOW_SCALE 20

typedef struct Display_t {
    SDL_Window * window;
    SDL_Renderer * renderer;
    int width;
    int height;
} Display_t ;


Display_t * createDisplay(int width, int height, char * title);
void destroyDisplay(Display_t ** display);

void renderDisplay(Display_t * display, FrameBuffer_t * buffer);
void handleEvent(SDL_Event * event);
