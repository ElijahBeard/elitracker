#pragma once
#include <SDL2/SDL.h>

SDL_Event event;

void ip_handle() {
    // TODO:
    // This will handle all inputs. No rendering will be done here.
    // Use functions from pattern.h in ip_handle to manipulate the data structures
    // Data structures will then be rendered via ui header

    while (SDL_PollEvent( &event ) != 0) {
        switch(event.type) {
            case SDL_QUIT:
                running = 0;
                break;
        }
    }
}

int send_midi_message(uint32_t status, uint32_t note, uint32_t velocity) {
    // status = 0x90 for Note On, 0x80 for Note Off
    // note = 60 for Middle C
    
    return 0;
}

// TODO:
// Write a function that uses SDL polling to turn keyboard actions into MIDI messages to put into a Midi event queue
// Midi event queue will later be accessed by nonexistent midi.h file and used for audio playback
void handle_keyboard_midi(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_z: return send_midi_message(0x90, 60, 64); break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_z: note = 50 + (12 * oct); break;
        }
    }
}