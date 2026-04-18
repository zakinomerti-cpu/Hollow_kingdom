[[person_data]]
[[player_data]]
[[toolBox]]

тип данных.

Задачи:
1) Сохранить результат обработки ввода( platform.h занимается обработкой ввода).
2) хранить массивы персон
3) хранить псевдокласс игрока

```c  
typedef struct {  
byte input;  
  
player p; 
  
person* persons; 
int person_count;  
  
byte current_scene; // IDLE=0 / COMBAT=1 / PRISON=2  
byte current_enemy_id; // индекс текущего врага  
  
} gameState;
```