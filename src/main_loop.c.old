#include "main_loop.h"

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SUCCESS_CODE 0

//############### Args Def ###############
int RECTSIZE;
int ADNSIZE;
double SPEED;
double ROTATIONSPEED;
int NPOP;
int PLAYMODE;

//########## SDL & Controls def ##########
static Input IN;
static SDL_bool QUIT;
static SDL_Window* WINDOW;
static SDL_Renderer* RENDERER;

//############### Run def ################
int RUNNING;
int STEP;
int FRAME;

//########## Creature array def ##########
static Creature* creatureArray;


int main(int argc, char** argv)
{
	//############################### Args init ###############################
	if (argc != 7)
	{
		printf(	
			"[RECTSIZE] [ADNSIZE] [SPEED] [ROTATIONSPEED] [NPOP] [PLAYMODE] [CORENBR]\n"
			"\n"
			"[RECTSIZE] = 0 : Point, switch the renderer to draw point (faster)\n"
			"\n"
			"[PLAYMODE] = 0 : Step by step, (type space-bar to show next frame)\n"
			"[PLAYMODE] = 1 : Continuous, (type space-bar to pause/play)\n"
			"\n"
		);

		return -1;
	}

	sscanf(argv[2], "%d", &ADNSIZE);
	sscanf(argv[3], "%lf", &SPEED);
	sscanf(argv[4], "%lf", &ROTATIONSPEED);
	sscanf(argv[5], "%d", &NPOP);
	sscanf(argv[6], "%d", &PLAYMODE);

	printf("############################### Args init ###############################\n");
	printf("Creature size      : %d\n", RECTSIZE);
	printf("ADN size            : %d\n", ADNSIZE);
	printf("Speed               : %lf\n", SPEED);
	printf("Rotation Speed      : %lf\n", ROTATIONSPEED);
	printf("Population size     : %d\n", NPOP);
	PLAYMODE == 0 ? printf("Play mode           : step by step\n") : printf("Play mode           : continuous\n");
	printf("\n");
	printf("\n");


	//###############################	Creature init	###############################

	creature_init_array(&creatureArray, NPOP);

	//###############################	RectZone init	###############################
	RectZone obstacleArray[] = {
		[1] = {
			.x = WIDTH/2,
			.y = HEIGHT/2,
			.w = 200,
			.h = 200,
			.color = {255, 0, 0, SDL_ALPHA_OPAQUE},
			.angle = 0,
			.isObstacle = 1
		},

		[2] = {
			.x = WIDTH/3,
			.y = HEIGHT/3,
			.w = 200,
			.h = 200,
			.color = {255, 0, 0, SDL_ALPHA_OPAQUE},
			.angle = 0,
			.isObstacle = 1
		},
		
		[3] = {
			.x = WIDTH/4*3,
			.y = HEIGHT/4*3,
			.w = 200,
			.h = 200,
			.color = {255, 0, 0, SDL_ALPHA_OPAQUE},
			.angle = 0,
			.isObstacle = 1
		}
	};

	//initObstacleArray(obstacleArray);
	
	RectZone goal = {
		WIDTH-100,
		HEIGHT-100,
		100,
		200,
		{0, 255, 0, SDL_ALPHA_OPAQUE},
		0,
		0
	};


	//###############################	SDL init	###############################
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != SUCCESS_CODE)
	{
		fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Init Input array
	memset(&IN, 0, sizeof(IN));


	//############### Run init ################
	RUNNING = 0;
	STEP = 0;

	//###############################	Window init	###############################
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &WINDOW, &RENDERER) != SUCCESS_CODE)
	{	
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
		SDL_Quit();
		return SDL_WINDOWPOS_UNDEFINED;
	}

	//###############################	Initialize SDL_ttf library	###############################
	if (TTF_Init() != 0)
    {
        fprintf(stderr,"TTF_Init failed: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }

	// Load the font
	TTF_Font* font = TTF_OpenFont("C:/Windows/Fonts/consola.ttf", 24);
	if (!font)
	{
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return 1;
	}

	SDL_Color textColor = {255, 255, 255, 255}; // White text

	// pas ouf
	Uint64 startTicks = SDL_GetPerformanceCounter();
	Uint64 endTicks = SDL_GetPerformanceCounter();
	float elsapsed_ms;
	float avgFPS;
	char avgFPSText[32];
	//
	
	SDL_Rect textRect;
	textRect.x = 0;
	textRect.y = 0;
	SDL_Surface *textSurface;
	SDL_Texture *text;

	//###############################	SDL	Loop	###############################
	while (!QUIT && !IN.key[SDL_SCANCODE_ESCAPE])
	{
		startTicks = SDL_GetPerformanceCounter();

		//*** Analytic loop ***
		FRAME++;


		//*** Event loop ***
		UpdateEvents(&IN, &QUIT);


		//*** Physic loop ***
		//IIII number of frame = size of ADN IIII
		if (STEP < ADNSIZE)
		{

			run_physic_frame(PLAYMODE);

			if (STEP == (ADNSIZE) + 1)
				printf("Generation finished\n");
		}


		//*** Render loop ***
		//** Creature render **
		SDL_RenderClear(RENDERER);
		for(int i = 0; i < NPOP; i++)
		{
			creature_draw(&creatureArray[i], RENDERER);
		}

		endTicks = SDL_GetPerformanceCounter();

		elsapsed_ms = (endTicks - startTicks) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(16.666f - elsapsed_ms));
		sprintf(avgFPSText, "FPS: %f", 1.0f/(elsapsed_ms/1000.0f));

		
		//** text render **
		textSurface = TTF_RenderText_Solid(font, avgFPSText, textColor);
		text = SDL_CreateTextureFromSurface(RENDERER, textSurface);

		SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderCopy(RENDERER, text, NULL, &textRect);

		// Update screen
		SDL_RenderPresent(RENDERER);
		

		//SDL renderer chore
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);



	}

	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void run_physic_frame(int playMode)
{
	if(playMode == 0)
	{
		if (IN.key[SDL_SCANCODE_RIGHT] == 1)
		{
			STEP +=1;
			IN.key[SDL_SCANCODE_RIGHT] = 0;
			for( int i = 0; i < NPOP; i++)
			{
				creature_directional_rotate(&creatureArray[i], STEP);
				creature_move(&creatureArray[i], STEP);
			}
		}
	}
	else
	{

		if (IN.key[SDL_SCANCODE_SPACE] == 1)
		{
			IN.key[SDL_SCANCODE_SPACE] = 0;
			RUNNING = RUNNING == 0 ? 1 : 0;
		}

		if(RUNNING == 1)
		{ 
			STEP +=1;
			for( int i = 0; i < NPOP; i++)
			{
				creature_directional_rotate(&creatureArray[i], STEP);
				creature_move(&creatureArray[i], STEP);
			}
		}
	}
}