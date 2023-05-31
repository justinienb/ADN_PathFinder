#include "rect_life.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

extern int RECTSIZE;
extern int ADNSIZE;
extern double SPEED;
extern double ROTATIONSPEED;

int createRect(RectLife* rect, int size)
{
		rect->size = size;
		rect->x = INIT_X;
		rect->y = INIT_Y;
		if (RANDOM_START_ANGLE_BOOL == 1)
			rect->angle = rand()%360 * M_PI/180;
		else
			rect->angle = 0;
		rect->color.r = rand()%256;
		rect->color.g = rand()%256;
		rect->color.b = rand()%256;
		rect->color.a = SDL_ALPHA_OPAQUE;

		rect->dead = 0;
		rect->win = 0;

		rect->moveAdn = (uint8_t*)malloc(ADNSIZE*sizeof(uint8_t));
		for(int i = 0; i < ADNSIZE; i++)
		{
			rect->moveAdn[i] = (uint8_t)rand()%MAX_RAND;
		}

		rect->speedAdn = (uint8_t*)malloc(ADNSIZE*8*sizeof(uint8_t));
		for(int i = 0; i < ADNSIZE*8; i++)
		{
			rect->speedAdn[i] = (uint8_t)rand()%MAX_RAND;
		}
		return 1;
}


int moveRect(RectLife* rect, int index)
{
	rect->x = rect->x + SPEED * rect->speedAdn[index] * cos(rect->angle);
	rect->y = rect->y + SPEED * rect->speedAdn[index] * sin(rect->angle);
	return 1;
}


int rotateRectDir(RectLife* rect, int index)
{
	uint8_t dir = readDirectionBit(rect->moveAdn, index);
	if (dir == 0)
	{
		rect->angle += ROTATIONSPEED;
	} else{
		rect->angle -= ROTATIONSPEED;
	}
	return 1;
}


int rotateRect(RectLife* rect, double rad)
{
	rect->angle += rad;
	return 1;
}


int readDirectionBit(uint8_t* moveAdn, int index)
{
	// printf("############################### Read Bit Index n°%d	###############################\n");
	int segment = index/(sizeof(uint8_t)*8);
	// printf("Segment n°%d	: ", segment);
	// printBits(sizeof(uint8_t), &moveAdn[segment]);

	uint8_t mask = 0x01 << index%8;
	// printf("\nmask		: ");
	// printBits(sizeof(uint8_t), &mask);

	uint8_t dir = 0;
	dir = (moveAdn[segment] & mask);
	// printf("\ndir		: ", dir);
	// printBits(sizeof(uint8_t), &dir);
	// printf("\n");

	return dir;
}


// Assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
}

// In progress
// int ColiderEngine(RectLife* lifeArray, RectZone* zoneArray, int nPop){

// 	int lifePointArray[4];
// 	int obstaclePointArray[4];
	
// 	int lax;
// 	int lbx;
// 	int lcx;
// 	int ldx;
// 	int lay;
// 	int lby;
// 	int lcy;
// 	int ldy;
	
// 	int oax;
// 	int obx;
// 	int ocx;
// 	int odx;
// 	int oay;
// 	int oby;
// 	int ocy;
// 	int ody;


// 	for (int i = 0; i < nPop; i++){

// 		double curentAngle = lifeArray[i].angle;
// 		curentAngle += M_PI_4;

// 		int targetX1 = lifeArray[i].size/2 * cos(curentAngle) + lifeArray[i].x;
// 		int targetY1 = lifeArray[i].size/2 * sin(curentAngle) + lifeArray[i].y;
// 		curentAngle += M_PI_2;
// 	}

// 	return 1;
// }

int initRectArray(RectLife rectArray[], int sizeRect, int nPop)
{
	for(int i = 0; i < nPop; i++)
	{
		createRect(&rectArray[i], sizeRect);
	}

	return 1;
}

int drawRect(RectLife* rect, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, rect->color.r, rect->color.g, rect->color.b, rect->color.a);

	double curentAngle = rect->angle;
	curentAngle += M_PI_4;

	for(int i = 0; i < 4; i++)
	{
		int targetX1 = rect->size/2 * cos(curentAngle) + rect->x;
		int targetY1 = rect->size/2 * sin(curentAngle) + rect->y;
		curentAngle += M_PI_2;
		int targetX2 = rect->size/2 * cos(curentAngle) + rect->x;
		int targetY2 = rect->size/2 * sin(curentAngle) + rect->y;

		SDL_RenderDrawLine(renderer, targetX1, targetY1, targetX2, targetY2);
	}
	return 1;
}