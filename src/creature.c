#include "creature.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

extern int RECTSIZE;
extern int ADNSIZE;
extern double SPEED;
extern double ROTATIONSPEED;

int creature_init_array(Creature** creature_array, int npop)
{
	*creature_array = malloc(npop*sizeof(Creature));
	for(int i = 0; i < npop; i++)
	{
		creature_create(&(*creature_array)[i]);
	}

	return 1;
}


int creature_create(Creature* creature)
{
		creature->x = INIT_X;
		creature->y = INIT_Y;
		if (RANDOM_START_ANGLE_BOOL == 1)
			creature->angle = rand()%360 * M_PI/180;
		else
			creature->angle = 0;
		creature->color.r = rand()%256;
		creature->color.g = rand()%256;
		creature->color.b = rand()%256;
		creature->color.a = SDL_ALPHA_OPAQUE;

		creature->dead = 0;
		creature->win = 0;

		creature->moveAdn = (uint8_t*)malloc(ADNSIZE*sizeof(uint8_t));
		for(int i = 0; i < ADNSIZE; i++)
		{
			creature->moveAdn[i] = (uint8_t)rand()%MAX_RAND;
		}

		creature->speedAdn = (uint8_t*)malloc(ADNSIZE*sizeof(uint8_t));
		for(int i = 0; i < ADNSIZE; i++)
		{
			creature->speedAdn[i] = (uint8_t)rand()%MAX_RAND;
		}
		return 1;
}


int creature_move(Creature* creature, int index)
{
	creature->x = creature->x + SPEED * creature->speedAdn[index] * cos(creature->angle);
	creature->y = creature->y + SPEED * creature->speedAdn[index] * sin(creature->angle);
	return 1;
}

int creature_rotate(Creature* rect, double rad)
{
	rect->angle += rad;
	return 1;
}


int creature_directional_rotate(Creature* rect, int index)
{
	uint8_t dir = creature_read_direction_bit_internal(rect->moveAdn, index);
	if (dir == 0)
	{
		rect->angle += ROTATIONSPEED;
	} else{
		rect->angle -= ROTATIONSPEED;
	}
	return 1;
}


int creature_read_direction_bit_internal(uint8_t* moveAdn, int index)
{
	// printf("############################### Read Bit Index no %d	###############################\n");
	int segment = index/(sizeof(uint8_t)*8);
	//printf("Segment no %d	: ", segment);
	//printBits(sizeof(uint8_t), &moveAdn[segment]);

	uint8_t mask = 0x01 << index%8;
	//printf("\nmask		: ");
	//printBits(sizeof(uint8_t), &mask);

	uint8_t dir = 0;
	dir = (moveAdn[segment] & mask);
	//printf("\ndir		: ");
	//printBits(sizeof(uint8_t), &dir);
	//printf("\n");

	return dir;
}


// Assumes little endian
void creature_print_bits_internal(size_t const size, void const * const ptr)
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

int creature_draw(Creature* creature, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, creature->color.r, creature->color.g, creature->color.b, creature->color.a);
	SDL_RenderDrawPoint(renderer, creature->x, creature->y);

	return 1;
}