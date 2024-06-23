#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>

// Structure to hold input states
typedef struct {
    int key[SDL_NUM_SCANCODES];
} Input;

// Function prototypes for handling events
void event_update(Input* in, SDL_bool* quit);

#endif // EVENT_H
