[[person_data]]
Описание:
Обертка callback для класса персоны. 


поля псевдокласса:
```c
byte person_id;
byte (*person_process)(person* p);
```


интерфейс псевдокласса:
```c
byte create(byte pId, byte (*person_process)(person* p));
byte update(gameState* gs);
```


деструктор:  отсутствует.