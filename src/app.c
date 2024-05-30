#include "app.h"
#include "init.h"

#include "creature.h"
#include "event.h"
#include "population.h"


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

int running;
int step;

static SDL_bool QUIT = SDL_FALSE;
static SDL_Window* WINDOW = NULL;
static SDL_Renderer* RENDERER = NULL;
static TTF_Font* FONT = NULL;
static Creature* creatureArray = NULL;
static Input IN = {0};

// Function to initialize SDL and other components
int app_init(char** argv) {
    // Parse command-line arguments
    sscanf(argv[2], "%d", &ADNSIZE);
    sscanf(argv[3], "%lf", &SPEED);
    sscanf(argv[4], "%lf", &ROTATIONSPEED);
    sscanf(argv[5], "%d", &NPOP);
    sscanf(argv[6], "%d", &PLAYMODE);

    printf("############################### Args init ###############################\n");
    printf("ADN size            : %d\n", ADNSIZE);
    printf("Speed               : %lf\n", SPEED);
    printf("Rotation Speed      : %lf\n", ROTATIONSPEED);
    printf("Population size     : %d\n", NPOP);
    PLAYMODE == 0 ? printf("Play mode           : step by step\n") : printf("Play mode           : continuous\n");
    printf("\n");

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    // Create SDL window and renderer
    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &WINDOW, &RENDERER) != 0) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return 0;
    }

    // Load the font
    FONT = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 24);
    if (!FONT) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return 0;
    }

    // Initialize the population of creatures
    if (!population_init(&creatureArray, NPOP)) {
        fprintf(stderr, "Failed to initialize population\n");
        TTF_CloseFont(FONT);
        TTF_Quit();
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(WINDOW);
        SDL_Quit();
        return 0;
    }

    return 1;
}

// Function to run the main application loop
void app_run() {
    Uint64 startTicks, endTicks;
    float elapsed_ms, avgFPS;
    char avgFPSText[32];
    SDL_Rect textRect = {0, 0, 0, 0};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* textSurface = NULL;
    SDL_Texture* text = NULL;

    running = 0;
    step = 0;


    while (!QUIT) {
        startTicks = SDL_GetPerformanceCounter();

        // Update events
        event_update(&IN, &QUIT);

        if (&IN.key[SDL_SCANCODE_SPACE] == 1) {
            running = !running;
        }
        // Update population
        population_update(creatureArray, PLAYMODE, &IN);

        // Clear renderer
        SDL_RenderClear(RENDERER);

        // Render population
        population_draw(creatureArray, RENDERER);

        // Calculate and render FPS
        endTicks = SDL_GetPerformanceCounter();
        elapsed_ms = (endTicks - startTicks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        // Delay to cap at 60 FPS
        SDL_Delay(fmax(0, 16.666f - elapsed_ms));

        avgFPS = 1.0f / ((elapsed_ms + fmax(0, 16.666666f - elapsed_ms)) / 1000.0f);
        sprintf(avgFPSText, "FPS: %f", avgFPS);

        textSurface = TTF_RenderText_Solid(FONT, avgFPSText, textColor);
        text = SDL_CreateTextureFromSurface(RENDERER, textSurface);
        SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(RENDERER, text, NULL, &textRect);

        // Present renderer
        SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(RENDERER);

        // Clean up text rendering
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(text);
    }
}

void app_draw_fps(){

}

// Function to clean up SDL and other components
void app_cleanup() {
    population_free(&creatureArray);
    TTF_CloseFont(FONT);
    TTF_Quit();
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}