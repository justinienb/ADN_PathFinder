#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>
#include "init.h"

#define _USE_MATH_DEFINES
#define RANDOM_START_ANGLE_BOOL 0

typedef struct
{
    int x;
    int y;
    int w;
    int h;
    SDL_Color color;
    float angle;
    int isObstacle;
} RectZone;


#endif
