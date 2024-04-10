#include "main_loop.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

//########## RectLife array def ##########
static RectLife* rectArray;


int main(int argc, char** argv)
{
	//############################### Args init ###############################
	if (argc != 7)
	{
		printf(	
			"[RECTSIZE] [ADNSIZE] [SPEED] [ROTATIONSPEED] [NPOP] [PLAYMODE] [CORENBR]\n"
			"\n"
			"[PLAYMODE] = 0 : Step by step, (type space-bar to show next frame)\n"
			"[PLAYMODE] = 1 : Continuous, (type space-bar to pause/play)\n"
			"\n"
		);

		return -1;
	}

	sscanf(argv[1], "%d", &RECTSIZE);
	sscanf(argv[2], "%d", &ADNSIZE);
	sscanf(argv[3], "%lf", &SPEED);
	sscanf(argv[4], "%lf", &ROTATIONSPEED);
	sscanf(argv[5], "%d", &NPOP);
	sscanf(argv[6], "%d", &PLAYMODE);

	printf("############################### Args init ###############################\n");
	printf("Rectangle size      : %d\n", RECTSIZE);
	printf("ADN size            : %d\n", ADNSIZE);
	printf("Speed               : %lf\n", SPEED);
	printf("Rotation Speed      : %lf\n", ROTATIONSPEED);
	printf("Population size     : %d\n", NPOP);
	PLAYMODE == 0 ? printf("Play mode           : step by step\n") : printf("Play mode           : continuous\n");
	printf("\n");
	printf("\n");


	//###############################	RectLife init	###############################
	initRectArray(&rectArray, RECTSIZE, NPOP);

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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0 )
	{
		fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
		return EXIT_FAILURE;
	}
	//Init Input array
	memset(&IN,0,sizeof(IN));


	//############### Run init ################
	RUNNING = 0;
	STEP = 0;

	//###############################	Window init	###############################
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &WINDOW, &RENDERER) != 0)
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

	Uint32 startTicks = SDL_GetTicks();
	float avgFPS;
	char avgFPSText[32];

	SDL_Rect textRect;
	textRect.x = 0;
	textRect.y = 0;
	SDL_Surface *textSurface;
	SDL_Texture *text;

	//###############################	SDL	Loop	###############################
	while (!QUIT && !IN.key[SDL_SCANCODE_ESCAPE])
	{
		FRAME++;

		avgFPS = FRAME / ((SDL_GetTicks() - startTicks) / 1000.f);
		
		sprintf(avgFPSText, "FPS: %f", avgFPS);

		textSurface = TTF_RenderText_Solid(font, avgFPSText, textColor);
		text = SDL_CreateTextureFromSurface(RENDERER, textSurface);


		SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

		SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(RENDERER);

		//IIII number of frame = size of ADN IIII
		if (STEP < ADNSIZE)
		{

			runFrame(PLAYMODE);

			if (STEP == (ADNSIZE) + 1)
				printf("Generation finished\n");
		}

		for(int i = 0; i < NPOP; i++)
		{
			drawPoint(&rectArray[i], RENDERER);
		}

		
		// Render text
		SDL_RenderCopy(RENDERER, text, NULL, &textRect);

		// Update screen
		SDL_RenderPresent(RENDERER);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(text);
	
		UpdateEvents(&IN, &QUIT);
	}

	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void runFrame(int playMode)
{
	if(playMode == 0)
	{
		if (IN.key[SDL_SCANCODE_RIGHT] == 1)
		{
			STEP +=1;
			IN.key[SDL_SCANCODE_RIGHT] = 0;
			for( int i = 0; i < NPOP; i++)
			{
				rotateRectDir(&rectArray[i], STEP);
				moveRect(&rectArray[i], STEP);
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
				rotateRectDir(&rectArray[i], STEP);
				moveRect(&rectArray[i], STEP);
			}
		}
	}
}