#include "sceneManager.h"
#include "platform.h"
#include "stdio.h"

int main(int argc, char** argv) {
	platform plt = {0};
	glutPlatform_init(&plt, argc, argv);

	sceneManager sm = {0};
	sceneManagerInit(&sm, &plt);

	sm.ops->run(&sm);
	sm.ops->destroy(&sm);

	printf("12\n");
	return 0;

}