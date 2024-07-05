#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Function prototypes for the application
int app_init(char** argv);
void app_run();
void app_cleanup();
int app_next_step_control(int run_next_step);

// the diferent state of the application are described here :

typedef enum {
    MAIN_MENU, // begining state
    SIMULATION, // state when simumating (will simulate next step)
    LEVEL_DESIGNER // state when making level design
} App_state;

typedef struct {
    App_state current_state;
    SDL_bool quit;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Input input;
} App_context;


#endif // APP_H