#include "population.h"
#include "creature.h"
#include "event.h"

#include <stdlib.h>

// Define NPOP to access the number of creatures globally
extern int NPOP;
extern int running;
extern int step;


// Initialize the population of creatures
int population_init(Creature** creatureArray, int numCreatures) {
    *creatureArray = malloc(numCreatures * sizeof(Creature));
    if (*creatureArray == NULL) {
        return 0; // Allocation failed
    }
    
    for (int i = 0; i < numCreatures; i++) {
        creature_init(&(*creatureArray)[i]);
    }
    return 1;
}

// Update the state of the population based on the play mode and input
void population_update(Creature* creatureArray, int playMode, Input* input) {

    if (playMode == 0) { // Step-by-step mode
        if (input->key[SDL_SCANCODE_RIGHT] == 1) {
            step += 1;
            input->key[SDL_SCANCODE_RIGHT] = 0;
            for (int i = 0; i < NPOP; i++) {
                creature_directional_rotate(&creatureArray[i], step);
                creature_move(&creatureArray[i], step);
            }
        }
    } else { // Continuous mode
        if (input->key[SDL_SCANCODE_SPACE] == 1) {
            input->key[SDL_SCANCODE_SPACE] = 0;
            running = !running;
        }
        
        if (running == 1) {
            step += 1;
            for (int i = 0; i < NPOP; i++) {
                creature_directional_rotate(&creatureArray[i], step);
                creature_move(&creatureArray[i], step);
            }
        }
    }
}

// Draw the population of creatures
void population_draw(Creature* creatureArray, SDL_Renderer* renderer) {
    for (int i = 0; i < NPOP; i++) {
        creature_draw(&creatureArray[i], renderer);
    }
}

// Free the memory allocated for the population
void population_free(Creature** creatureArray) {
    for (int i = 0; i < NPOP; i++) {
        creature_free(&(*creatureArray)[i]);
    }
    free(*creatureArray);
    *creatureArray = NULL;
}