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

int SIMULATION_STEP;


static SDL_bool QUIT = SDL_FALSE;
static SDL_Window* WINDOW = NULL;
SDL_Renderer* RENDERER = NULL;
static TTF_Font* FONT = NULL;
static Input IN = {0};

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
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Load the font
    FONT = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 24);
    if (FONT == NULL) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Initialize the population of creatures
    if (population_init() == EXIT_FAILURE) {
        fprintf(stderr, "Failed to initialize population\n");
        TTF_CloseFont(FONT);
        TTF_Quit();
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if(level_init() == EXIT_FAILURE){
        fprintf(stderr, "Failed to initialize level\n");
        TTF_CloseFont(FONT);
        TTF_Quit();
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// Function to run the main application loop
void app_run() {
    Uint64 start_ticks, endTicks;
    float elapsed_ms, avgFPS;
    char avgFPSText[32];
    SDL_Rect textRect = {0, 0, 0, 0};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = NULL;
    SDL_Texture* text = NULL;

    int run_next_step = 0;
    SIMULATION_STEP = 0;
    
    while (!QUIT) {
        start_ticks = SDL_GetPerformanceCounter();

        // Update events
        event_update(&IN, &QUIT);

        run_next_step = app_next_step_control(run_next_step);

        if (run_next_step && SIMULATION_STEP <= ADNSIZE){
            SIMULATION_STEP++;
            // Update population
            population_update(SIMULATION_STEP);
        }
        
        // Clear renderer buffer with black pixel
        SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE); //select black opaque
        SDL_RenderClear(RENDERER); // turn all pixel in renderer buffer to black (background)

        // Render level
        level_draw(RENDERER);

        // Render population
        population_draw(RENDERER); // draw the little creature on top of the background

        // Calculate and render FPS
        endTicks = SDL_GetPerformanceCounter();
        elapsed_ms = (endTicks - start_ticks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // Delay to cap at 60 FPS
        SDL_Delay(fmax(0, 16.666f - elapsed_ms));

        avgFPS = 1.0f / ((elapsed_ms + fmax(0, 16.666666f - elapsed_ms)) / 1000.0f);
        sprintf(avgFPSText, "FPS: %f", avgFPS);

        textSurface = TTF_RenderText_Solid(FONT, avgFPSText, textColor);
        text = SDL_CreateTextureFromSurface(RENDERER, textSurface);
        SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(RENDERER, text, NULL, &textRect);
        
        //render buffer to screen
        SDL_RenderPresent(RENDERER);
    }
        
        //if QUIT, then clean up text rendering
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(text);
}

void app_draw_fps(){

}

// Function to clean up SDL and other components
void app_cleanup() {
    population_free();
    TTF_CloseFont(FONT);
    TTF_Quit();
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}

int app_next_step_control(int run_next_step)
{
    if (PLAYMODE == 0)
    { // Step-by-step mode
        if (IN.key[SDL_SCANCODE_RIGHT] == 1)
        {
            IN.key[SDL_SCANCODE_RIGHT] = 0;
            run_next_step = 1;
        }
        else
        {
            run_next_step = 0;
        }
    }
    else
    { // Continuous mode
        if (IN.key[SDL_SCANCODE_SPACE] == 1)
        {
            IN.key[SDL_SCANCODE_SPACE] = 0;
            run_next_step = !run_next_step;
        }
    }
    return run_next_step;
}