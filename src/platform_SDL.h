#pragma once 

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


typedef struct Display_t {
    SDL_Window * window;
    SDL_Renderer * renderer;
    int width;
    int height;
} Display_t ;


Display_t * createDisplay(int width, int height, char * title);
void destroyDisplay(Display_t ** display);

void renderDisplay(Display_t * display);
void handleEvent(SDL_Event * event);
