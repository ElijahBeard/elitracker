#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "util.h"

#define _WIN_W_ 800
#define _WIN_H_ 600
int running = 1;

SDL_Event event;
SDL_Window* window = NULL;
SDL_Renderer* renderer;

SDL_Rect dest;
SDL_Texture* texture = NULL;
TTF_Font* font = NULL;

int init_tracker() {
    // SDL windowing
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) { printf("SDL Init Fail: %s\n", SDL_GetError()); return 1; }
    if ( TTF_Init() < 0 ) { printf("TTF Init Fail: %s\n", TTF_GetError()); return 1; }

    window = SDL_CreateWindow(
        "eli tracker",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        _WIN_W_,_WIN_H_,SDL_WINDOW_SHOWN
    ); if(!window) { printf("%s",SDL_GetError()); return 2; }

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
    if(!renderer) { printf("Renderer Fail: %s\n", SDL_GetError()); return 3; }
    
    // font stuff
    font = TTF_OpenFont(font_path, 15); 
    if (!font) { 
        printf("Font Load Fail: %s\n", TTF_GetError()); 
        return 4;
    }

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, "G* .. 50 A6", color);
    if (!surface) { printf("Surface Fail: %s\n", TTF_GetError()); return 5; }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    dest.x = 0;
    dest.y = 0;
    dest.w = surface->w;
    dest.h = surface->h;
    
    SDL_FreeSurface(surface);
    return 0;
}

void ip_handle() {
    while (SDL_PollEvent( &event ) != 0) {
        switch(event.type) {
            case SDL_QUIT:
                running = 0;
                break;
        }
    }
}

int t_render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_RenderPresent(renderer);
    return 0;
}

void quit_tracker() {
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}