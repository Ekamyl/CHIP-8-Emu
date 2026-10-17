#include <stdlib.h>
#include "platform_SDL.h"                           
 
int main(int argc, char *argv[])
{
    
    Display_t * display = createDisplay(64 * 20, 32 * 20, "Chip8-Emu") ;
    SDL_Event event ;
    
    do {
        
        handleEvent(&event);
        renderDisplay(display);

    } while (event.type != SDL_EVENT_QUIT) ;

    destroyDisplay(&display);
    SDL_Quit();

    return 0;
}
