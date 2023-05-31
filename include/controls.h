#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>

typedef struct
{
    char key[SDL_NUM_SCANCODES];
} Input;


// Functions
void UpdateEvents(Input* in, SDL_bool* quit);

// End of header file
#endif
