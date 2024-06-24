#ifndef CONTROL_H
#define CONTROL_H

#include <SDL2/SDL.h>

typedef struct {
    int x, y;
} Start;


typedef struct {
    int x, y;
} End;


typedef struct {
    SDL_Rect zone;
} Obstacle;

int level_init();
int level_add_obstacle(int x, int y, int w, int h);
void level_draw();

#endif // CONTROL_H
