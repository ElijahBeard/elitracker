#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ui.h"
#include "pattern.h"

int main(void) {
    if(init_tracker() != 0) {perror("Init Failed\n"); return 1;}
    init_pattern();
    iter_pattern();
    while (running) {
        ip_handle();
        t_render();
    }
    SDL_Delay(16);
}