#ifndef POPULATION_H
#define POPULATION_H

#include "creature.h"
#include "event.h"

#include <SDL2/SDL.h>

// Function prototypes for population management
int population_init();
void population_update(int simulation_step);
void population_draw();
void population_cleanup();

#endif // POPULATION_H