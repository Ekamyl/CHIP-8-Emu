#include <stdlib.h>
#include <time.h>
#include "platform_SDL.h"                           
#include "chip8.h"

#define MS_PER_FRAME 16

/* Main program entry point for the emulator. */
int main(int argc, char *argv[])
{
    
    // Create the SDL window and set up the display.
    Display_t * display = createDisplay(DISPLAY_WIDTH * WINDOW_SCALE, DISPLAY_HEIGHT * WINDOW_SCALE, "Chip8-Emu") ;
    SDL_Event event ;
    Chip8_t chip8 = initChip8();

    // Keep track of time for the frame limiter.
    uint64_t last_time = SDL_GetTicks();
    uint64_t current_time;

    // Count frames to display the FPS every second.
    uint8_t fps = 0;
    uint64_t last_time_fps = SDL_GetTicks();
    uint64_t current_time_fps;

    // Seed the random generator for opcode operations that need random values.
    srand(time(NULL));

    do {
        
        // Handle user events and keep the emulator running.
        handleEvent(&event, &chip8);
        runChip8(&chip8, 10);
        renderDisplay(display, &chip8.frame_buffer);
        fps++;

        
        // Update the FPS count once each second.
        current_time_fps = SDL_GetTicks();
        if ((current_time_fps - last_time_fps) >= 1000) {
            printf("fps : %d\n", fps);
            fps = 0;
            last_time_fps = current_time_fps;
        }


        // Keep the loop at roughly 60 FPS.
        current_time = SDL_GetTicks();
        if ((current_time - last_time) < 16) {
            SDL_Delay(MS_PER_FRAME - (current_time - last_time));
        }
        last_time = SDL_GetTicks();

    } while (event.type != SDL_EVENT_QUIT && chip8.running == TRUE) ;

    destroyDisplay(&display);
    SDL_Quit();

    return 0;
}
