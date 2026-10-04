#include "idle.h"
#include "raylib.h"

static void init() {
}

static void draw() {
	ClearBackground((Color){128, 64, 64, 255});
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


scene idleScene() {
	scene b;
	b.ops = &ops;
	b.isInit = 1;
	return b;
}
