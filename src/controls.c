#include "controls.h"

#include <stdio.h>
#include <SDL2/SDL.h>


void UpdateEvents(Input* in, SDL_bool* quit)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.scancode]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.scancode]=0;
			break;
		case SDL_QUIT:
			*quit = SDL_TRUE;
			break;
		default:
			break;
		}
	}
}

void UpdateControls()
{

}
