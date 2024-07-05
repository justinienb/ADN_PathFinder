#include "simulation.h"
#include "event.h"


extern int PLAYMODE;
extern Input IN;

int simulation_step = 0;
int run_next_step = 0;


void simulation_control(int* run_next_step)
{
    if (PLAYMODE == 0)
    { // Step-by-step mode
        if (IN.key[SDL_SCANCODE_RIGHT] == 1)
        {
            IN.key[SDL_SCANCODE_RIGHT] = 0;
            *run_next_step = 1;
        }
        else
        {
            *run_next_step = 0;
        }
    }
    else
    { // Continuous mode
        if (IN.key[SDL_SCANCODE_SPACE] == 1)
        {
            IN.key[SDL_SCANCODE_SPACE] = 0;
            *run_next_step = !*run_next_step;
        }
    }
}

void simulation_update(){

    simulation_control(&run_next_step);

    if (run_next_step && simulation_step <= ADNSIZE){
        simulation_step++;
        // Update population
        population_update(simulation_step);
    }

}


void simulation_draw(){
    // draw level into renderer buffer
    level_draw(RENDERER);

    // draw population into renderer buffer
    population_draw(RENDERER);
}

