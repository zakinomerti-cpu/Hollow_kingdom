#include "platform.h"
#include <string.h>
#include "raylib.h"

static void (*displayFunc)(void) = NULL;
static char shouldClose_ = 0;

static void platformInit(platform* plt) {

}
static void render(platform* plt) {
	BeginDrawing();
		if (displayFunc) displayFunc();
	EndDrawing();

	shouldClose_ = WindowShouldClose();
}
static void setStartFunc(platform* plt, void (*func)(void)) {

}
static void setDisplayFunc(platform* plt, void (*func)(void)) {
	displayFunc = func;
}
static unsigned char shouldClose(platform* plt) {
	return shouldClose_;
}

static const platformInterface ops = {
	platformInit,
	render,
	setStartFunc,
	setDisplayFunc,
	shouldClose,
};

void platform_init(platform* plt, const char* title, int x, int h) {
	if(!plt) return;
	plt->title = strdup(title);
	plt->width = x;
	plt->height = h;
	plt->ops = &ops;

	InitWindow(x, h, title);
}