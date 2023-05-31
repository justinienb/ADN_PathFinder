#include "main_loop.h"

#include <stdio.h>
#include <SDL2/SDL.h>

int RECTSIZE;
int ADNSIZE;
double SPEED;
double ROTATIONSPEED;
int NPOP;

Input IN;
SDL_bool QUIT;
SDL_Window* WINDOW;
SDL_Renderer* RENDERER;


int main(int argc, char** argv)
{
	//############################### Args init ###############################
	if (argc != 6)
	{
		printf("[RECTSIZE][ADNSIZE][SPEED][ROTATIONSPEED][NPOP]\n");
		return -1;
	}

	sscanf(argv[1], "%d", &RECTSIZE);
	sscanf(argv[2], "%d", &ADNSIZE);
	sscanf(argv[3], "%lf", &SPEED);
	sscanf(argv[4], "%lf", &ROTATIONSPEED);
	sscanf(argv[5], "%d", &NPOP);

	printf("############################### Args init ###############################\n");
	printf("Rectangle size		: %d\n", RECTSIZE);
	printf("ADN size		: %d\n", ADNSIZE);
	printf("Speed			: %lf\n", SPEED);
	printf("Rotation Speed		: %lf\n", ROTATIONSPEED);
	printf("Population size		: %d\n", NPOP);
	printf("\n");
	printf("\n");


	//###############################	RectLife init	###############################
	RectLife rectArray[NPOP];
	initRectArray(rectArray, RECTSIZE, NPOP);

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


	//###############################	Window init	###############################
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &WINDOW, &RENDERER) != 0)
	{	
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}


	//###############################	SDL	Loop	###############################
	int frameNum = 0;
	int step = 0;
	int pause = 1;
	while (!QUIT && !IN.key[SDL_SCANCODE_ESCAPE])
	{

		//########	Draw only size of adn	########
		if (frameNum < ADNSIZE*8)
		{
			SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(RENDERER);


			if(pause%2 == 0)
			{
				for( int i = 0; i < NPOP; i++)
				{
					rotateRectDir(&rectArray[i], frameNum);
					moveRect(&rectArray[i], frameNum);
				}
				frameNum +=1;
			}


			if (IN.key[SDL_SCANCODE_SPACE] == 1)
			{
				IN.key[SDL_SCANCODE_SPACE] = 0;
				pause++;
			}


			// if (IN.key[SDL_SCANCODE_RIGHT] == 1 && step == 1 || 1)
			// {
			// 	IN.key[SDL_SCANCODE_RIGHT] = 0;
			// 	step = 0;
			// for( int i = 0; i < NPOP; i++)
			// {
			// 	moveRect(&rectArray[i]);
			// }
			// }


			for( int i = 0; i < NPOP; i++)
			{
				drawRect(&rectArray[i], RENDERER);
			}

			SDL_RenderPresent(RENDERER);
		}
			

		UpdateEvents(&IN, &QUIT);
		//SDL_Delay(10);
	}

	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	return EXIT_SUCCESS;
}