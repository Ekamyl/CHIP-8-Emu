#include <stdlib.h>
#include "platform_SDL.h"


Display_t * createDisplay(int width, int height, char * title) {
    
    Display_t * display = malloc(1 * sizeof(Display_t)) ;
    display->width = width ;
    display->height = height ;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return NULL ;  
    }

    if (!SDL_CreateWindowAndRenderer(title, width, height, SDL_WINDOW_RESIZABLE, &display->window, &display->renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return NULL ;
    }

    return display ;
}


void destroyDisplay(Display_t ** display) {

    SDL_DestroyRenderer((*display)->renderer);
    SDL_DestroyWindow((*display)->window);
    free(*display);
    *display = NULL;

}


void renderDisplay(Display_t * display) {

    SDL_SetRenderDrawColor(display->renderer, 0, 150, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(display->renderer);
    SDL_RenderPresent(display->renderer);
    
}


void handleEvent(SDL_Event * event) {

    SDL_PollEvent(event); 

}
