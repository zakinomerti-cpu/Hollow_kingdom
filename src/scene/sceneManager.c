#include "sceneManager.h"
#include "platform.h"

static Scene* scene_ref;
static void display() {
	scene_ref->ops->draw(scene_ref);
}

//конкретная реализация игры
static void run(sceneManager* m) {
	if(!(m && m->isInit == 1)) return;

	int result = m->scn.ops->processLogic(&m->scn);
	while(!m->scn.plt->shouldClose(m->scn.plt) && result != -1)
	{

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
					//m->scn.gs.current_enemy_id = result;
				}
				break;
			}

			case 2: {
				if(result == 1) {
					//m->scn.gs.persons[m->scn.gs.current_enemy_id].is_imprisoned = 1;
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
			default: {
				m->scn.plt->render(m->scn.plt);
				result = m->scn.ops->processLogic(&m->scn);
			}
		}

	}
}

static void destroy(sceneManager* m) {
	m->scn.ops->destroy(&m->scn);
}

static const sceneManagerInterface ops = {
	run,
	destroy
};

void sceneManagerInit(sceneManager* m, platform* plt) {
	plt->setDisplayFunc(plt, display);
	plt->createWindow(plt, "window", 900, 900);
	plt->platformInit(plt);

	SceneInit(&m->scn, plt);
	scene_ref = &m->scn;

	m->scn.currentScene = 0;
	m->ops = &ops;
	m->isInit = 1;
}