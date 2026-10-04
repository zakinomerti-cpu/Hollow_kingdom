#ifndef scene_header_h
#define scene_header_h

struct scene;

typedef struct {
	void (*init)();
	int (*process)();
	void (*draw)();
	void (*destroy)();
} sceneInterface;

typedef struct scene {
	unsigned char isInit;
	const sceneInterface* ops;
} scene;

#endif
