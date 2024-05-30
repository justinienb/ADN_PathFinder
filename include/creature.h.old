#ifndef PIXELLIFE_H
#define PIXELLIFE_H

// #includes
#include <stdio.h>
#include "rect.h"
#include "init.h"

// structs
typedef struct
{
    float x;
    float y;
    SDL_Color color;
    float angle;
    int dead;
    int win;
    uint8_t* moveAdn;
    uint8_t* speedAdn;

} Creature;

// Functions
int creature_create(Creature* creature);
int creature_init_array(Creature** creature_array, int npop);

int creature_move(Creature* creature, int index);
int creature_rotate(Creature* creature, double rad);
int creature_directional_rotate(Creature* creature, int index);
int creature_read_direction_bit_internal(uint8_t* move_adn, int index);
int creature_draw(Creature* creature, SDL_Renderer* renderer);
void creature_print_bits_internal(size_t const size, void const * const ptr);

// End of header file
#endif
