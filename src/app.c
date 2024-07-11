#include "app.h"
#include "init.h"

#include "creature.h"
#include "event.h"
#include "population.h"
#include "level.h"
#include "fps.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 


// Global variables
int ADNSIZE;
double SPEED;
double ROTATIONSPEED;
int NPOP;
int PLAYMODE;


App_context app_context;

SDL_Window* WINDOW;
SDL_Renderer* RENDERER;
TTF_Font* FONT;

// Function to initialize SDL and other components
int app_init(char** argv) {

    // Parse command-line arguments
    sscanf(argv[1], "%d", &ADNSIZE);
    sscanf(argv[2], "%lf", &SPEED);
    sscanf(argv[3], "%lf", &ROTATIONSPEED);
    sscanf(argv[4], "%d", &NPOP);
    sscanf(argv[5], "%d", &PLAYMODE);

    printf("############################### Args init ###############################\n");
    printf("ADN size            : %d\n", ADNSIZE);
    printf("Speed               : %lf\n", SPEED);
    printf("Rotation Speed      : %lf\n", ROTATIONSPEED);
    printf("Population size     : %d\n", NPOP);
    PLAYMODE == 0 ? printf("Play mode           : step by step\n") : printf("Play mode           : continuous\n");
    printf("\n");



    //intialisation of context
    app_context.current_state = MAIN_MENU;
    app_context.quit = SDL_FALSE;
    app_context.input = (Input){0}; 

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == EXIT_FAILURE) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create SDL window and renderer
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &WINDOW, &RENDERER) == EXIT_FAILURE) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == EXIT_FAILURE) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        app_cleanup(&app_context);
        return EXIT_FAILURE;
    }

    // Load the font
    FONT = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 24);
    if (FONT == NULL) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        app_cleanup(&app_context);
        return EXIT_FAILURE;
    }

    // Initialize the population of creatures
    if (population_init() == EXIT_FAILURE) {
        fprintf(stderr, "Failed to initialize population\n");
        app_cleanup(&app_context);
        return EXIT_FAILURE;
    }

    if(level_init() == EXIT_FAILURE){
        fprintf(stderr, "Failed to initialize level\n");
        app_cleanup(&app_context);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


// function to clean up before making texture ect..
void app_cleanup() {

    //module cleanup;
    population_cleanup();
    fps_cleanup();

    if (FONT != NULL) {
        TTF_CloseFont(FONT);
    }
    TTF_Quit();
    if (RENDERER != NULL) {
        SDL_DestroyRenderer(RENDERER);
    }
    if (WINDOW != NULL) {
        SDL_DestroyWindow(WINDOW);
    }
    SDL_Quit();
}


// Function to run the main application loop
void app_run() {
    Uint64 start_ticks, last_frame_start_ticks, last_frame_end_ticks;
    float elapsed_ms, avgFPS;
    
    while (!app_context.quit) {
        //####################### Statistics #######################
        last_frame_start_ticks = start_ticks;
        start_ticks = SDL_GetPerformanceCounter();

        //calculate elapsed time of previous frame
        fps_calculate(last_frame_start_ticks, last_frame_end_ticks);
        fps_cap_60();


        event_update(&app_context.input, &app_context.quit);


        //#################### Drawing ####################

        //clean buffer and draw blakground
        app_draw_background();

        app_handle_state(&app_context.input);

        app_event_control();

        //draw statistics
        fps_draw();
        //####################### Rendering #######################
        //render buffer to screen
        SDL_RenderPresent(RENDERER);


        //####################### Statistics #######################
        last_frame_end_ticks = SDL_GetPerformanceCounter();
    }
    
    app_cleanup();
}




void app_draw_background(){

    //####################### Clearing Drawing buffer #######################
    // Clear renderer buffer with black pixel
    SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE); //select black opaque
    SDL_RenderClear(RENDERER); // turn all pixel in renderer buffer to black (background)
}


void app_draw_state() {
    switch (app_context.current_state) {
        case MAIN_MENU:
            menu_draw();
            break;
        case SIMULATION:
            simulation_draw();
            break;
        case LEVEL_DESIGNER:
            level_designer_draw();
            break;
    }
}


void app_update_state() {
    switch (app_context.current_state) {
        case MAIN_MENU:
            menu_update();
            break;
        case SIMULATION:
            simulation_update();
            break;
        case LEVEL_DESIGNER:
            level_designer_update();
            break;
    }
}