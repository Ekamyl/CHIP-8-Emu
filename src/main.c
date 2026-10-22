#include <stdlib.h>
#include "platform_SDL.h"                           
#include "chip8.h"

#define MS_PER_FRAME 16


int main(int argc, char *argv[])
{
    
    Display_t * display = createDisplay(64 * 20, 32 * 20, "Chip8-Emu") ;
    SDL_Event event ;
    Chip8_t chip8 = initChip8();

    // time variables 
    uint64_t last_time = SDL_GetTicks();
    uint64_t current_time;

    // frame counter 
    uint8_t fps = 0;
    uint64_t last_time_fps = SDL_GetTicks();
    uint64_t current_time_fps;

    do {
        
        // boucle d'evenement 
        handleEvent(&event);
        // runChip8(&chip8, 10);
        renderDisplay(display);
        fps++;

        
        // fps limiter 
        current_time = SDL_GetTicks();
        if ((current_time - last_time) < 16) {
            SDL_Delay(MS_PER_FRAME - (current_time - last_time));
        }
        last_time = SDL_GetTicks();


        // fps counter
        current_time_fps = SDL_GetTicks();
        if ((current_time_fps - last_time_fps) >= 1000) {
            printf("fps : %d\n", fps);
            fps = 0;
            last_time_fps = current_time_fps;
        }

    } while (event.type != SDL_EVENT_QUIT) ;

    destroyDisplay(&display);
    SDL_Quit();

    return 0;
}
