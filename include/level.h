#ifndef CONTROL_H
#define CONTROL_H

#include <SDL_rect.h>

typedef struct {
    int x, y;
} Start;


typedef struct {
    SDL_Rect zone;
} End;


typedef struct {
    SDL_Rect zone;
} Obstacle;

#endif // CONTROL_H
