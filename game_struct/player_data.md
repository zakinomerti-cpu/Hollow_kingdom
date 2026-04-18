Тип данных

```c
typedef struct {
	char name[32];
	float pos[3];
	byte abilityIds[MAX_ABILITIES];
	byte activeAbilityIds[MAX_ACTIVE_ABILITIES];
	byte ability_count;
} player;
```