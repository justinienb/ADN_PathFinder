int elapsed_ms;


void fps_cap_60(int last_frame_start_ticks, int last_frame_end_ticks)
{
    // Delay to cap at 60 FPS
    SDL_Delay(fmax(0, 16.666f - fps_calculate_elapsed_time(last_frame_start_ticks, last_frame_end_ticks)));
}



void fps_draw(int last_frame_start_ticks, int last_frame_end_ticks)
{
    //####################### statistics #######################
    // Calculate and render FPS


    int avgFPS = 1.0f / ((elapsed_ms + fmax(0, 16.666666f - elapsed_ms)) / 1000.0f);
    sprintf(avgFPSText, "FPS: %f", avgFPS);

    text_surface = TTF_RenderText_Solid(FONT, avgFPSText, textColor);
    text = SDL_CreateTextureFromSurface(RENDERER, text_surface);
    SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(RENDERER, text, NULL, &textRect);
}

int fps_calculate_elapsed_time(int last_frame_end_ticks, int last_frame_start_ticks)
{
    return (last_frame_end_ticks - last_frame_start_ticks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
}