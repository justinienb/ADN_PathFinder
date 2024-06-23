
#include "level.h"

extern RENDERER;

Obstacle obstacle_array[];

End goal;

Start start;

void level_add_obstacle(int x, int y, int w, int h){

}

void level_set_start(int x, int y, int w, int h){

}

void level_set_end(int x, int y, int w, int h){

}

void level_draw(){
    SDL_SetRenderDrawColor(RENDERER, creature->color.r, creature->color.g, creature->color.b, creature->color.a);
    SDL_RenderDrawPoint(renderer, round(creature->x), round(creature->y));
}