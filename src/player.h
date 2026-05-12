#ifndef player_header
#define player_header

#include <stdint.h>

typedef struct {
	char name[32];
	float pos[3];
	uint8_t abilityIds[64]; // где abilityIds[n] = 0 означает что этот и последующие элементы не заданы
	uint8_t activeAbilityIds[8]; // где activeAbilityIds[n] = 0 означает что этот и последующие элементы не заданы
} Player;

#endif