#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "pattern.h"

#define _WIN_W_ 800
#define _WIN_H_ 600

char* font_path = "dina10px.ttf";

SDL_Window* window = NULL;
SDL_Renderer* renderer;
TTF_Font* font = NULL;

// Rects
SDL_Texture* texture = NULL;
SDL_Rect dest;

// Colors
SDL_Color text_color = {255, 255, 255, 255};


int init_tracker_win() {
    // TODO:
    // This function will initialize the window the background skin e.g. everything that has to only blit once

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
    
    return 0;
}

int write_pattern() {
    // TODO:
    // Write a function that renders a single cell of text e.g. "C#3 07 -- A17" to the screen
    // This function will loop through the pattern and render each cell one by one

    font = TTF_OpenFont(font_path, 15); 
    if (!font) { 
        printf("Font Load Fail: %s\n", TTF_GetError()); 
        return 4;
    }

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, "--- 07 64 -00 C#3 07 64 D12 E-7 07 64 D12", text_color, (uint32_t){120});
    if (!surface) { printf("Surface Fail: %s\n", TTF_GetError()); return 1; }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    dest.x = 0;
    dest.y = 0;
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_FreeSurface(surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_RenderPresent(renderer);

    return 0;
}



int t_render() {
    write_pattern();
    return 0;
}

void quit_tracker() {
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}