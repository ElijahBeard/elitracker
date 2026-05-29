#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "core/t_headers.h"

int running = 1;

int main(void) {
    // if(init_tracker_win() != 0) {perror("Init Failed\n"); return 1;}
    pattern_t p;
    init_pattern(&p);
    test_pattern(&p);
    // while (running) {
    //     ip_handle();
    //     t_render();
    // }
    // SDL_Delay(16);
    return 0;
}