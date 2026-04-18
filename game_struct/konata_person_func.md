```c
void create_konata_person(person* persons, int index) {
	person konata;
	konata.id = 0;
	konata.hp = 255;
	konata.pos[0] = 5.0f;
	konata.pos[1] = 0.0f;
	konata.pos[2] = 10.0f;
	konata.adaptation_type = 0;
	konata.attack_damage = 15;
	konata.area_decor[0] = "konataStyleArena1.png";
	konata.area_decor[1] = "konataStyleArena2.png";
	konata.area_decor[2] = "konataStyleArena3.png";
	konata.area_decor[3] = "konataStyleArena4.png";
	konata.area_decor[4] = "konataStyleArena5.png";
	konata.area_decor[5] = "konataStyleArena6.png";
	konata.area_decor[6] = "konataStyleArena7.png";
	konata.area_decor[7] = "konataStyleArena8.png";
	konata.abilityIds[0] = 2;
	konata.abilityIds[1] = 5;
	konata.granted_ability_id = 2;
	konata.is_imprisoned = 0;
	strcpy(konata.name, "Konata Izumi");
	persons[index] = konata;
}
```