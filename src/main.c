#include "sceneManager.h"
#include "platform.h"

#include "mainMenu/mainMenu.h"

int main(int argc, char** argv) {
	platform plt = {0};
	platform_init(&plt, "platform", 800, 600);

	sceneManager sm = {0};
	sceneManager_init(&sm, &plt);

	scene s = mainMenuScene();
	sm.ops->add_scene(&sm, &s, "mainMenu");
	sm.ops->set_current(&sm, "mainMenu");

	sm.ops->run(&sm);
	sm.ops->destroy(&sm);
	return 0;

}