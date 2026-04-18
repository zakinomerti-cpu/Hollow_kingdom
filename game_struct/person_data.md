[[toolBox]] // предоставляет тип byte, color, 


```c
typedef struct {
	int id;
	byte hp; // 0 - 255
	char name[32];
	float pos[3];
	byte adaptation; // 1 - деградация, 0 - адаптация
	byte attack_damage; // 0 - 255
	char* area_decor[8]; // путь к 8 особым текстурам декора

	byte abilityIds[MAX_ACTIVE_ABILITIES];
	byte granted_ability_id;
	color palette;
	byte special[32]; // в зависимости от id 
	byte is_imprisoned; // 1 - свободна, 0 - в тюрьме
	byte ability_count;
} person;
```