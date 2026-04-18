#include "scene.h"
#include "platform.h"
#include "createPersons.h"
#include <string.h>



// setter and getter
static void _setCurrentScene(Scene* scn, unsigned char index) {
	if(!(scn && scn->isInit == 1)) return; //secure
	if(scn->sceneCount <= index) return;
	scn->currentScene = index;
}
static unsigned char _getCurrentSceneIndex(Scene* scn) {
		if(!(scn && scn->isInit == 1)) return 0; //secure
		return scn->currentScene;
}




// process
static int _processLogic(Scene* scn) {
	if(!(scn && scn->isInit == 1)) return -1;	// secure 
	int (*process)(SceneBucket* b, Scene* scn);
	unsigned char cur = scn->currentScene;


	// get pointer to ops and check init
	if(scn->sceneArray[cur].isInit != 1) return -1; // secure 
	process = scn->sceneArray[cur].ops->process;
	if(process != NULL) {
		return process(&scn->sceneArray[cur], scn);
	}
	return -1;
}
static void _draw(Scene* scn) { 
	if(!(scn && scn->isInit == 1)) return;
	void (*draw)(SceneBucket* b, Scene* scn);
	unsigned char cur = scn->currentScene;


	// get pointer to ops and check init
	if(scn->sceneArray[cur].isInit != 1) return; // secure 
	draw = scn->sceneArray[cur].ops->draw;
	if(draw != NULL) {
		draw(&scn->sceneArray[cur], scn);
	}
}
static void _destroy(Scene* scn) {
	if(!(scn && scn->isInit == 1)) return;
	for(int i = 0; i < scn->sceneCount; i++) {
		void (*destroy)(SceneBucket* b);

		// get pointer to ops and check init
		if(scn->sceneArray[i].isInit != 1) return; // secure 
		destroy = scn->sceneArray[i].ops->destroy;
		if(destroy != NULL) {
			destroy(&scn->sceneArray[i]);
		}
	}
}




// conf
static void _add(Scene* scn, SceneBucket b) {
	if(!(scn && scn->isInit == 1)) return; 
	scn->sceneArray[scn->sceneCount] = b;
	scn->sceneCount += 1;
}

static const SceneInterface ops = {
	_setCurrentScene,
	_getCurrentSceneIndex,

	//process
	_processLogic,
	_draw,
	_destroy,

	//conf
	_add,
};



void SceneInit(Scene* scn, platform* plt) {
	Player player = {0};
	strcpy(player.name, "magistor");
	player.pos[0] = 0.0f;
	player.pos[1] = 0.0f;
	player.pos[2] = 0.0f;
	player.abilityIds[0] = 0;
	player.activeAbilityIds[0] = 0;

	Person persons[1]; 
	createPersonArray(persons, 1);

	gameState gs = {0};
	gs.person_count = 1;
	gs.player = player;
	gs.current_enemy_id = -1;
	memcpy(gs.persons, persons, sizeof(persons));
	scn->gs = gs;

	scn->isInit = 1;
	scn->sceneCount = 0;
	scn->currentScene = -1;
	memset(scn->sceneArray, 0, sizeof(SceneBucket)*32);

	scn->plt = plt;
	scn->ops = &ops;
}