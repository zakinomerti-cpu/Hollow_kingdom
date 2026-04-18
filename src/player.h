#ifndef player_header
#define player_header

#include "toolBox.h"

typedef struct {
	char name[32];
	float pos[3];
	byte abilityIds[64]; // где abilityIds[n] = 0 означает что этот и последующие элементы не заданы
	byte activeAbilityIds[8]; // где activeAbilityIds[n] = 0 означает что этот и последующие элементы не заданы
} Player;

#endif