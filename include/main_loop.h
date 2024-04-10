#ifndef MAINLOOP_H
#define MAINLOOP_H

// #includes
#include "controls.h"
#include "rect_life.h"
#include "rect.h"
#include "init.h"

int main(int argc, char** argv);
void runFrame(int playMode);
int drawCore(void* threadArgs);

typedef struct 
{
    SDL_mutex* rendererLock;
    RectLife* rect;
    int idxFrom;
    int idxTo;
} ThreadArgs;

// End of header file
#endif
