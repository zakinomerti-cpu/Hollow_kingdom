#ifndef sceneManager_header
#define sceneManager_header

#include "scene.h"

//forward dec
struct sceneManager;
struct platform;



// interface
typedef struct {
	void (*run)(struct sceneManager* m);
	void (*destroy)(struct sceneManager* m);
} sceneManagerInterface;



// class defenition
typedef struct sceneManager {
	char isInit;
	struct Scene scn;
	sceneManagerInterface* ops;
} sceneManager;



// new
void sceneManagerInit(sceneManager* m, struct platform* plt);

#endif