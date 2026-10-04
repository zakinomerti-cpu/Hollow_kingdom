#ifndef sceneManager_header
#define sceneManager_header

//forward dec
struct sceneManager;
struct platform;

struct scene;
struct scnHashMap;



// interface
typedef struct {
	void (*run)(struct sceneManager* m);
	void (*add_scene)
	(
		struct sceneManager* m,
		struct scene* scn,
		const char* scn_name
	);
	void (*set_current)
	(
		struct sceneManager* m,
		const char* name
	);
	void (*destroy)(struct sceneManager* m);
} sceneManagerInterface;



// class defenition
typedef struct sceneManager {
	char isInit;
	struct scnHashMap* hMap;
	const sceneManagerInterface* ops;
} sceneManager;



// new
void sceneManager_init(sceneManager* m, struct platform* plt);

#endif