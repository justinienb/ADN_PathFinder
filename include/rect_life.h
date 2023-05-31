#ifndef RECTLIFE_H
#define RECTLIFE_H

// #includes
#include <stdio.h>
#include "rect.h"
#include "init.h"

// structs
typedef struct
{
    float x;
    float y;
    int size;
    SDL_Color color;
    float angle;
    int dead;
    int win;
    uint8_t* moveAdn;
    uint8_t* speedAdn;

} RectLife;



// Functions
int createRect(RectLife* rect, int size);
int moveRect(RectLife* rect, int index);
int rotateRect(RectLife* rect, double rad);
int rotateRectDir(RectLife* rect, int index);
int readDirectionBit(uint8_t* moveAdn, int index);
int ColiderEngine(RectLife* lifeArray, RectZone* zoneArray, int nPop);
int initRectArray(RectLife rectArray[], int sizeRect, int nPop);
int drawRect(RectLife* rect, SDL_Renderer* renderer);

// End of header file
#endif
