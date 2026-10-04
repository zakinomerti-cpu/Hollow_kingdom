#include "sceneManager.h"
#include "platform.h"
#include "scene.h"

#include "scnHashMap.h"
#include <stddef.h>

static platform*	gpPlatform		= NULL;
static scene*		pCurrnetScene	= NULL;

//конкретная реализация игры
static void _run(sceneManager* m) {
	if(!m || !m->isInit || !pCurrnetScene) return;
	// главный цикл игры
	pCurrnetScene->ops->init();
	while(!gpPlatform->ops->shouldClose(gpPlatform)) {
		pCurrnetScene->ops->process();
		gpPlatform->ops->render(gpPlatform);
	}
}

static void _destroy(sceneManager* m) {

}

static void add_scene(sceneManager* m, scene* s, const char* name) {
	if (!m || !m->isInit || !s || !s->isInit || !name) return;
	m->hMap->ops->put(m->hMap, name, sizeof(name)-1, s);
}

static void set_current(sceneManager* m, const char* name) {
	if (!m || !m->isInit || !name) return;

	scene* s = NULL;
	int result = m->hMap->ops->get(m->hMap, name, sizeof(name)-1, &s);
	if (result != HA_OUTCODE_OK) return;

	gpPlatform->ops->setDisplayFunc(gpPlatform, s->ops->draw);
	pCurrnetScene = s;
}

static const sceneManagerInterface ops = {
	_run,
	add_scene,
	set_current,
	_destroy
};

void sceneManager_init(sceneManager* m, platform* plt) {
	gpPlatform = plt;
	m->ops = &ops;
	m->isInit = 1;
	scnHashMap_new(&m->hMap, 64);
}