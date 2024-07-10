#include "app.h"
#include "init.h"

#include "creature.h"
#include "event.h"
#include "population.h"
#include "level.h"


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



    //intialisation bateau du contexte
    app_context.current_state = MAIN_MENU;
    app_context.quit = SDL_FALSE;
    app_context.window = NULL;
    app_context.renderer = NULL;
    app_context.font = NULL;
    app_context.input = (Input){0}; 

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == EXIT_FAILURE) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create SDL window and renderer
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &app_context.window, &app_context.renderer) == EXIT_FAILURE) {
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
    app_context.font = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 24);
    if (app_context.font == NULL) {
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
void app_cleanup(App_context *context) {
    if (context->font != NULL) {
        TTF_CloseFont(context->font);
    }
    TTF_Quit();
    if (context->renderer != NULL) {
        SDL_DestroyRenderer(context->renderer);
    }
    if (context->window != NULL) {
        SDL_DestroyWindow(context->window);
    }
    SDL_Quit();
}

// Function to clean up SDL and other components
void app_cleanup(App_context *context, SDL_Surface* text_surface, SDL_Texture* text) {
    //if QUIT, then clean up text rendering
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text);
    population_free();
    
    app_cleanup(&context);
}


// Function to run the main application loop
void app_run() {
    Uint64 start_ticks, last_frame_start_ticks, last_frame_end_ticks;
    float elapsed_ms, avgFPS;
    char avgFPSText[32];
    SDL_Rect textRect = {0, 0, 0, 0};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* text_surface = NULL;
    SDL_Texture* text = NULL;
    
    while (!app_context.quit) {
        //####################### Statistics #######################
        last_frame_start_ticks = start_ticks;
        start_ticks = SDL_GetPerformanceCounter();



        event_update(&app_context.input, &app_context.quit);

        //start counter and draw background
        app_loop_start_routine(&start_ticks);


        

        //#################### Drawing ####################

        //clean buffer and draw blakground
        app_draw_background();

        app_handle_state(&app_context.input);

        app_event_control();

        //draw statistics
        app_statistics_draw(last_frame_start_ticks, last_frame_end_ticks);

        //####################### Rendering #######################
        //render buffer to screen
        SDL_RenderPresent(app_context.renderer);


        //####################### Statistics #######################
        last_frame_end_ticks = SDL_GetPerformanceCounter();
    }
    
    app_cleanup(text_surface, text);
}




void app_draw_background(){

    //####################### Clearing Drawing buffer #######################
    // Clear renderer buffer with black pixel
    SDL_SetRenderDrawColor(app_context.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //select black opaque
    SDL_RenderClear(app_context.renderer); // turn all pixel in renderer buffer to black (background)
}


void app_draw_state(App_context context) {
    switch (context.current_state) {
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


void app_update_state(App_context context) {
    switch (context.current_state) {
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








//################################# Unused function #################################



