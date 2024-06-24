#ifndef CREATURE_H
#define CREATURE_H

#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct {
    float x, y;
    float angle;
    SDL_Color color;
    uint8_t* rotate_adn;
    uint8_t speed;
    uint8_t dead;
    uint8_t win;
} Creature;

// Function prototypes for creature management
void creature_init(Creature* creature);
void creature_free(Creature* creature);
void creature_move(Creature* creature);
void creature_rotate(Creature* creature, double rad);
void creature_directional_rotate(Creature* creature, int index);
void creature_draw(Creature* creature);
int creature_read_direction_bit_internal(uint8_t* rotate_adn, int index);
void creature_print_bits_internal(size_t const size, void const * const ptr);

#endif // CREATURE_H