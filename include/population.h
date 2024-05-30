#ifndef POPULATION_H
#define POPULATION_H

#include "creature.h"
#include "event.h"

#include <SDL2/SDL.h>

// Function prototypes for population management
int population_init(Creature** creatureArray, int numCreatures);
void population_update(Creature* creatureArray, int playMode, Input* input);
void population_draw(Creature* creatureArray, SDL_Renderer* renderer);
void population_free(Creature** creatureArray);

#endif // POPULATION_H