
#include "level.h"
#include "init.h"
#include <stdlib.h>
#include <SDL2/SDL.h>


extern SDL_Renderer* RENDERER;

//Obstacle obstacle_array[];
SDL_Rect* obstacle_array;
int obstacle_array_size;

Start start;
End end;

SDL_Color obstacle_color = {.r = 255, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE};

SDL_Color end_color = {.r = 0, .g = 255, .b = 0, .a = SDL_ALPHA_OPAQUE };

SDL_Color start_color = {.r = 0, .g = 0, .b = 255, .a = SDL_ALPHA_OPAQUE };

int level_init(){

    obstacle_array_size = 0;
    start.x = 10;
    start.y = HEIGHT/2;

    end.x = WIDTH-10;
    end.y = HEIGHT/2;

    int status = EXIT_SUCCESS; //  success is 0, failure is 1
    
    status += level_add_obstacle(100, 100, 100, 200);
    status += level_add_obstacle(300, 250, 50, 200);
    status += level_add_obstacle(250, 100, 100, 50);

    if (status != EXIT_SUCCESS){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int level_add_obstacle(int x, int y, int w, int h){
    obstacle_array_size++;

    obstacle_array = realloc(obstacle_array, obstacle_array_size * sizeof(SDL_Rect));
    if (obstacle_array == NULL) {
        return EXIT_FAILURE; // Allocation failed
    }

    SDL_Rect new_obstacle = {.x = x, .y = y, .w = w, .h = h};
    obstacle_array[obstacle_array_size-1] = new_obstacle;

    return EXIT_SUCCESS;
}

void level_draw(){
    //draw the start pixel from where all the pixel are from
    SDL_SetRenderDrawColor(RENDERER, start_color.r, start_color.g, start_color.b, start_color.a);
    SDL_RenderDrawPoint(RENDERER, start.x, start.y);

    //draw the end pixel
    SDL_SetRenderDrawColor(RENDERER, end_color.r, end_color.g, end_color.b, end_color.a);
    SDL_RenderDrawPoint(RENDERER, end.x, end.y);

    //draw the obstacles
    SDL_SetRenderDrawColor(RENDERER, obstacle_color.r, obstacle_color.g, obstacle_color.b, obstacle_color.a);
    //for each obstacle draw the obstacle
    for (int i = 0; i < obstacle_array_size; i++){
        SDL_RenderFillRect(RENDERER, &obstacle_array[i]);
    }
}