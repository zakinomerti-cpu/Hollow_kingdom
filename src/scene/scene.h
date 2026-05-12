#ifndef scene_header_h
#define scene_header_h

struct Scene;
struct platform;
struct SceneBucket;

typedef struct {
	int (*process)(struct SceneBucket*, struct Scene*);
	void (*draw)(struct SceneBucket*, struct Scene*);
	void (*destroy)(struct SceneBucket*);
} SceneBucketInterface;

typedef struct SceneBucket {
	unsigned char isInit;
	const SceneBucketInterface* ops;
} SceneBucket;

typedef struct {
	//setter and getter
	void (*setCurrentScene)(struct Scene*, unsigned char);
	unsigned char (*getCurrentSceneIndex)(struct Scene*);
	
	//process
	int (*processLogic)(struct Scene*);
	void (*draw)(struct Scene*);
	void (*destroy)(struct Scene*);

	//conf
	void (*add)(struct Scene*, SceneBucket bucket);
} SceneInterface;

typedef struct Scene {
	unsigned char isInit;
	unsigned char sceneCount;
	int currentScene;
	SceneBucket sceneArray[32];

	struct platform* plt;
	const SceneInterface* ops;

} Scene;

void SceneInit(Scene* scn, struct platform* plt);

#endif
