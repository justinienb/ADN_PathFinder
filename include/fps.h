#ifndef FPS_H
#define FPS_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>


// Function prototypes for FPS management
void fps_calculate_elapsed_time(int last_frame_end_ticks, int last_frame_start_ticks);
void fps_cap_60();
void fps_draw();

#endif // CREATURE_H