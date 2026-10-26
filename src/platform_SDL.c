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


void renderDisplay(Display_t * display, FrameBuffer_t * buffer) {

    if (buffer->modified) {

        buffer->modified = 0;

        SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(display->renderer);

        SDL_FRect rects[DISPLAY_WIDTH * DISPLAY_HEIGHT];
        uint16_t count = 0;

        for (int y = 0; y < DISPLAY_HEIGHT; y++) {
            for (int x = 0; x < DISPLAY_WIDTH; x++) {
                if (buffer->buffer[y] >> (63 - x) & 0x1) {
                    rects[count++] = (SDL_FRect){x * WINDOW_SCALE, y * WINDOW_SCALE, WINDOW_SCALE, WINDOW_SCALE};
                }
            }
        }

        if (count) {
            SDL_SetRenderDrawColor(display->renderer, 170, 170, 170, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRects(display->renderer, rects, count);
        }
        SDL_RenderPresent(display->renderer);
        
    }

}


void handleEvent(SDL_Event * event) {

    SDL_PollEvent(event); 

}
