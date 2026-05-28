#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_CHANNELS 8
#define MAX_ROWS 16

enum effect {
    EFFECT_EMPTY = 0,
    DELAY,
    REVERB,
    CHORUS
    // and so on
};

enum note {
    NOTE_EMPTY = 0,
    C, CS,
    D, DS,
    E,
    F,
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
    note_t pitch;       // C0 C#4 D3 etc...
    uint8_t instrument; // 0-64 instrument
    uint8_t vol;        // 0-64 volume level
    uint8_t fx;
    uint8_t fx_param;
} row_t;

typedef struct {
    bool active;
    row_t rows[MAX_ROWS];
} channel_t;

typedef struct {
    channel_t channels[MAX_CHANNELS];
} pattern_t;

pattern_t pattern = {0};

/*-----------------------------*/

const char* note_to_string(uint8_t note) {
    static const char* names[] = {
        "---",
        "C-",
        "C#",
        "D-",
        "D#",
        "E-",
        "E#",
        "F-",
        "F#",
        "G-",
        "G#",
        "A-",
        "A#",
        "B-"
    };
    if (note == NOTE_OFF)
        return "~~~";
    if (note >= sizeof(names) / sizeof(names[0]))
        return "???";
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

void print_note(note_t* n) {
    if (n->note == NOTE_EMPTY || n->note == NOTE_OFF) {
        printf("%s",note_to_string(n->note));
    } else {
        printf("%s%d",note_to_string(n->note),n->octave);
    }
}

void print_row(row_t* row) {
    print_note(&row->pitch);
    printf(" %02d %02d %s%02d",
        row->instrument, row->vol, fx_to_string(row->fx), row->fx_param
    );
}

static inline row_t row(uint8_t note, uint8_t octave, uint8_t instrument, uint8_t vol, uint8_t fx, uint8_t fx_param) {
    return (row_t){(note_t){note,octave},instrument,vol,fx,fx_param};
}

int init_pattern()
{
    pattern.channels[0].active = true;
    pattern.channels[0].rows[0] = row(NOTE_EMPTY,3,7,64,REVERB,00);
    pattern.channels[0].rows[1] = row(CS,3,7,64,DELAY,12);
    pattern.channels[0].rows[2] = row(NOTE_OFF,7,7,64,DELAY,12);
    pattern.channels[0].rows[3] = row(E,7,7,64,DELAY,12);
    return 0;
}

void iter_pattern() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int ch = 0; ch < MAX_CHANNELS; ch++)
        {
            channel_t *c = &pattern.channels[ch];

            if (!c->active)
                continue;

            row_t *r = &c->rows[row];
            
            // print_row(r);
            // printf("\n");
        }
    }
}