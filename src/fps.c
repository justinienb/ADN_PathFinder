#include "fps.h"


#define AVGLEN 5

extern TTF_Font* FONT;
extern SDL_Renderer* RENDERER;



char avgFPSText[32];
SDL_Rect textRect = {0, 0, 0, 0};
SDL_Color textColor = {255, 255, 255, 255};;
SDL_Surface* text_surface = NULL;
SDL_Texture* text = NULL;

int elapsed_ms = 0;
float avgFpsBuffer[AVGLEN];


//initialise the 
void fps_init()
{
    SDL_memset(avgFpsBuffer, 0.0, AVGLEN);
    elapsed_ms = 0;
}

// NEED TO BE CALLED FIRST IN ORDER FO OTHER FUNCTIONS TO WORK
void fps_calculate_elapsed_time(int last_frame_end_ticks, int last_frame_start_ticks)
{
    elapsed_ms = (last_frame_end_ticks - last_frame_start_ticks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
}


// does nothing if elapsed_ms has not a meaningfull value (0)
void fps_cap_60()
{
    if (!elapsed_ms)
        SDL_Delay(fmax(0, 16.666f - elapsed_ms));     // Delay to cap at 60 FPS
}


// does nothing if elapsed_ms has not a meaningfull value (0)
void fps_draw(int step)
{
    //####################### statistics #######################
    // Calculate and render FPS

    if (!elapsed_ms && step > 0)
    {   
        avgFpsBuffer[step%AVGLEN] = 1.0f / ((elapsed_ms + fmax(0, 16.666666f - elapsed_ms)) / 1000.0f);
        
        if (step%AVGLEN == 0)
        {
            float avgFPSsum = 0;
            for(int i = 0; i < AVGLEN; i++)
                avgFPSsum+= avgFpsBuffer[i];

            float avgFPS = avgFPSsum/AVGLEN;
            sprintf(avgFPSText, "FPS: %f", avgFPS);
            text_surface = TTF_RenderText_Solid(FONT, avgFPSText, textColor);
            text = SDL_CreateTextureFromSurface(RENDERER, text_surface);
            SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderCopy(RENDERER, text, NULL, &textRect);
        }
        
    }
}

void fps_cleanup()
{
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text);
}