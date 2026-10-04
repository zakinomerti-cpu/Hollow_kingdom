#include "mainMenu.h"
#include "raylib.h"

static void init() {
}

static void draw() {
	ClearBackground((Color){64, 64, 64, 255});
}

static int process() {

	return 0;
}

static void destroy() {

}

static const sceneInterface ops = {
	init,
	process,
	draw,
	destroy
};

scene mainMenuScene() {
	scene menu;
	menu.ops = &ops;
	menu.isInit = 1;
	return menu;
}


