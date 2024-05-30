#include "creature.h"
#include "init.h"

#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


extern int ADNSIZE;
extern double SPEED;
extern double ROTATIONSPEED;

void creature_init(Creature* creature) {
    creature->x = CREATURE_INIT_X; // Replace with appropriate initial x position
    creature->y = CREATURE_INIT_Y; // Replace with appropriate initial y position
    creature->angle = 0;
    creature->color.r = rand() % 256;
    creature->color.g = rand() % 256;
    creature->color.b = rand() % 256;
    creature->color.a = SDL_ALPHA_OPAQUE;
    creature->dead = 0;
    creature->win = 0;

    creature->rotate_adn = (uint8_t*)malloc(ADNSIZE * sizeof(uint8_t));
    for (int i = 0; i < ADNSIZE; i++) {
        creature->rotate_adn[i] = (uint8_t)rand() % 2;
    }

    creature->speed_adn = (uint8_t*)malloc(ADNSIZE * sizeof(uint8_t));
    for (int i = 0; i < ADNSIZE; i++) {
        creature->speed_adn[i] = (uint8_t)rand() % 256;
    }
}

void creature_free(Creature* creature) {
    free(creature->rotate_adn);
    free(creature->speed_adn);
}

void creature_move(Creature* creature, int index) {
    creature->x += SPEED * creature->speed_adn[index] * cos(creature->angle);
    creature->y += SPEED * creature->speed_adn[index] * sin(creature->angle);
}

void creature_rotate(Creature* creature, double rad) {
    creature->angle += rad;
}

void creature_directional_rotate(Creature* creature, int index) {
    uint8_t dir = creature->rotate_adn[index % ADNSIZE];
    if (dir == 0) {
        creature->angle += ROTATIONSPEED;
    } else {
        creature->angle -= ROTATIONSPEED;
    }
}

void creature_draw(Creature* creature, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, creature->color.r, creature->color.g, creature->color.b, creature->color.a);
    SDL_RenderDrawPoint(renderer, creature->x, creature->y);
}

//##########################################################################################################
//##########################################################################################################
//##########################################################################################################

// those function are for debugging purpose :
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