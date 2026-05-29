// @file pattern.h
// contains data structures for holding songdata

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_CHANNELS 8
#define MAX_ROWS 16

// TODO:
// Find a way to define the 'currently selected cell and edited attribute'
// For editing purposes

enum flags {
    HAS_NOTE = 1 << 0,
    HAS_INSTRUMENT = 1 << 1,
    HAS_VOLUME = 1 << 2,
    HAS_EFFECT = 1 << 3
};

enum effect {
    EFFECT_EMPTY = 0,
    DELAY,
    REVERB,
    CHORUS
};

enum note {
    NOTE_EMPTY = 0,
    C, CS,
    D, DS,
    E,
    F, FS,
    G, GS,
    A, AS,
    B,
    NOTE_OFF = 255
};

typedef struct {
    uint8_t note;
    uint8_t octave;
} note_t;

typedef struct {
    uint8_t flags;
    note_t pitch;       // C0 C#4 D3 etc...
    uint8_t instrument; // 0-64 instrument
    uint8_t vol;        // 0-64 volume level
    uint8_t fx;
    uint8_t fx_param;
} cell_t;

typedef struct {
    cell_t cells[MAX_ROWS][MAX_CHANNELS];
} pattern_t;

pattern_t pattern;

const char* note_to_string(uint8_t note) {
    static const char* names[] = {
        "--",
        "C-",
        "C#",
        "D-",
        "D#",
        "E-",
        "F-",
        "F#",
        "G-",
        "G#",
        "A-",
        "A#",
        "B-"
    };
    if (note == NOTE_OFF)
        return "~~";
    if (note >= sizeof(names) / sizeof(names[0]))
        return "??";
    return names[note];
}

const char* fx_to_string(uint8_t fx) {
    static const char* label[] = {
        "-", // Effect Empty
        "D", // Delay
        "R", // Reverb
        "C", // Chorus
    };
    return label[fx];
}

static void print_cell(cell_t* cell) {
    if(!(cell->flags & HAS_NOTE)) {printf("---");}
    else if (cell->pitch.note == NOTE_OFF) {printf("~~~");}
    else {printf("%s%d",note_to_string(cell->pitch.note),cell->pitch.octave);}
    printf(" ");
    if(!(cell->flags & HAS_INSTRUMENT)) {printf("--");}
    else{printf("%02d",cell->instrument);}
    printf(" ");
    if(!(cell->flags & HAS_VOLUME)) {printf("--");}
    else{printf("%02d",cell->vol);}
    printf(" ");
    if(!(cell->flags & HAS_EFFECT)) {printf("-");}
    else{printf("%s",fx_to_string(cell->fx));}
    printf("%02d",cell->fx_param);
    // printf("\n");
}

static inline cell_t empty_cell(void) { return (cell_t) {0}; }
// Note Edit
static inline void cell_set_note(cell_t* cell, uint8_t note, uint8_t octave) {
    cell->pitch.note = note; cell->pitch.octave = octave;
    cell->flags |= HAS_NOTE;
}
static inline void cell_clear_note(cell_t* cell) { cell->flags &= ~HAS_NOTE; }
//Instr Edit
static inline void cell_set_instrument(cell_t* cell, uint8_t instrument) {
    cell->instrument = instrument;
    cell->flags |= HAS_INSTRUMENT;
}
static inline void cell_clear_instrument(cell_t* cell) { cell->flags &= ~HAS_INSTRUMENT; }
//Volume Edit
static inline void cell_set_volume(cell_t* cell, uint8_t volume) {
    cell->vol = volume;
    cell->flags |= HAS_VOLUME;
}
static inline void cell_clear_volume(cell_t* cell) { cell->flags &= ~HAS_VOLUME; }
//FX Edit
static inline void cell_set_fx(cell_t* cell, uint8_t effect) {
    cell->fx = effect;
    cell->flags |= HAS_EFFECT;
}
static inline void cell_clear_fx(cell_t* cell) { cell->flags &= ~HAS_EFFECT; }
//FX Params Edit
static inline void cell_set_fx_params(cell_t* cell, uint8_t param) { cell->fx_param = param; }

int init_pattern(pattern_t* pattern)
{
    // TODO:
    // Set current cell to top left
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int ch = 0; ch < MAX_CHANNELS; ch++) {
            pattern->cells[row][ch] = empty_cell();
        }
    }
    return 0;
}

// When SDL timer step, playback.h reads a cell
// sets key_status current_note current_octave current_volume current_intstrument
// per channel / voice

// DEBUG FUNCTIONS
void print_pattern(pattern_t* p) { // Debug Only
    for(int row = 0; row < MAX_ROWS; row++) {
        printf("%02d | ", row);
        for (int ch = 0; ch < MAX_CHANNELS; ch++) {
            cell_t* cell = &p->cells[row][ch];
            print_cell(cell);
            printf(" | ");
        }
        printf("\n");
    }
}

void test_pattern(pattern_t* p) {
    init_pattern(&pattern);
    cell_set_note(&pattern.cells[0][0],C,4);
    cell_set_instrument(&pattern.cells[0][0],1);
    cell_set_volume(&pattern.cells[0][0],64);
    cell_set_fx(&pattern.cells[0][0],DELAY);
    cell_set_fx_params(&pattern.cells[0][0],12);
    cell_set_note(&pattern.cells[4][0],NOTE_OFF,0);
    print_pattern(&pattern);
}