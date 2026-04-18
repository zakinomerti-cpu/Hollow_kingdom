[[scene_class]]
[[idle.h]]
[[combat.h]]
[[prison.h]]
[[gameState_data]]
[[toolBox]]

// IDLE
// 0      -> PRISON
// 1..N   -> COMBAT (enemy_id = result - 1)

// COMBAT
// 0 -> return to IDLE scene
// 1 -> to PRISON scene

// PRISON
// 0 -> IDLE

Задачи:
1) инициализировать сцены.
2) запустить главный игровой цикл.
3) обработать результаты работы сцен.
4) организовать процесс передачи данных между сценами и реакцию на результаты работы функций сцен.