#include "sceneManager.h"
#include "platform.h"

#include "idle.h"
#include "mainMenu.h"

static Scene* scene_ref;
static void _display() {
	scene_ref->ops->draw(scene_ref);
}

//конкретная реализация игры
static void _run(sceneManager* m) {
	if(!(m && m->isInit == 1)) return;

	int result = -1;
	int game_shouldClose = 0;
	while(!m->scn.plt->shouldClose(m->scn.plt) && !game_shouldClose) 
	{

		result = m->scn.ops->processLogic(&m->scn); // единоразовый обработчик логики
		if(result == -1) game_shouldClose = -1;
		switch(m->scn.currentScene) // в зависимости от текущей сцены.
		{
			case 0: {
				if(result == 1) {
					m->scn.currentScene = 1;
				}
				break;
			}
			case 1: {
				if(result == 1) {
					m->scn.currentScene = 3;
				}
				if(result == -2) {
					m->scn.currentScene = 0;
				}
				if(result > 1) {
					m->scn.currentScene = 2;
					m->scn.gs.current_enemy_id = result;
				}
				break;
			}

			case 2: {
				if(result == 1) {
					m->scn.gs.persons[m->scn.gs.current_enemy_id].is_imprisoned = 1;
				}
				if(result == 2) {
					m->scn.currentScene = 1;
				}
				break;
			}

			case 3: {
				if(result == 1) {
					m->scn.currentScene = 1;
				}
				break;
			}
		}

		// отрисовка после блока обработки логики
		m->scn.plt->render(m->scn.plt);
	}
}

static void _destroy(sceneManager* m) {
	m->scn.ops->destroy(&m->scn);
}

static const sceneManagerInterface ops = {
	_run,
	_destroy
};

void sceneManagerInit(sceneManager* m, platform* plt) {
	plt->setDisplayFunc(plt, _display);
	plt->createWindow(plt, "window", 900, 900);
	plt->platformInit(plt);

	SceneInit(&m->scn, plt);
	scene_ref = &m->scn;

	m->scn.ops->add(&m->scn, mainMenuScene());
	m->scn.ops->add(&m->scn, idleScene());
	m->scn.currentScene = 0;
	m->ops = &ops;
	m->isInit = 1;
}