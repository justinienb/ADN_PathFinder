#ifndef POPULATION_H
#define POPULATION_H

#include "creature.h"
#include "event.h"

#include <SDL2/SDL.h>

// Function prototypes for population management
int population_init();
void population_update(int simulation_step);
void population_draw(SDL_Renderer* renderer);
void population_free();

#endif // POPULATION_H