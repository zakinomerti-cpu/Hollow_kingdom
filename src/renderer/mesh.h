#ifndef mesh_header
#define mesh_header

#include "pVoidArray.h"
struct Mesh;

typedef struct {
	float x; float y; float z;
	float nx; float ny; float nz;
	float u; float v;
} MeshVertex;

// можно добавлять точки до тех пор, пока не будет вызван init
typedef struct {
	void (*draw)(struct Mesh*);
	void (*destroy)(struct Mesh*);

	void (*addFace)(struct Mesh*, MeshVertex (*)[4]);
	void (*init)(struct Mesh*);
} MeshInterface;

typedef struct {
	struct pVoidArray vertices;
	struct pVoidArray indices;
	unsigned int vbo;
	unsigned int ibo;
} MeshPrivate;


//isInit = 1; object created
//isInit = 2; all faces set up
typedef struct Mesh {
	char isInit;
	const MeshInterface* ops;
	MeshPrivate _private;
} Mesh;

Mesh meshCreate();

#endif