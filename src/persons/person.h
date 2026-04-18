#ifndef person_header
#define person_header

#include "toolBox.h" // typedef unsigned char byte 

typedef struct {
	int id;
	byte hp; // 0 - 255
	char name[32];
	float pos[3];
	byte adaptation_type;
	byte attack_damage; // 0 - 255
	char* area_decor[8]; // путь к 8 особым текстурам декора

	byte abilityIds[8];
	byte granted_ability_id;
	byte palette[3]; // цветовая палитра персонажа
	byte special[32]; // в зависимости от id 
	byte is_imprisoned; // 1 - свободна, 0 - в тюрьме
	byte ability_count;
} Person;

#endif