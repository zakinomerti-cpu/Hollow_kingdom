#ifndef gameState_header
#define gameState_header

#include "toolBox.h"
#include "player.h"
#include "person.h"

typedef struct {
	Player player;
	Person persons[32];
	int person_count;
	int current_enemy_id;
} gameState;

#endif