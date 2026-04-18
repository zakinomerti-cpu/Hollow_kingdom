#include "baseGeometry.h"


// создает законченную геометрию
Mesh createCube(float size, float pos[3], float rot[3]) {
	Mesh m = meshCreate();
	float s = size / 2.0f;
	MeshVertex face[4];

	face[0] = (MeshVertex){-s, -s,  s,  1,1,1, 0,0};
	face[1] = (MeshVertex){ s, -s,  s,  1,1,1, 1,0};
	face[2] = (MeshVertex){ s,  s,  s,  1,1,1, 1,1};
	face[3] = (MeshVertex){-s,  s,  s,  1,1,1, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){ s, -s, -s,  0.8,0.8,0.8, 0,0};
	face[1] = (MeshVertex){-s, -s, -s,  0.8,0.8,0.8, 1,0};
	face[2] = (MeshVertex){-s,  s, -s,  0.8,0.8,0.8, 1,1};
	face[3] = (MeshVertex){ s,  s, -s,  0.8,0.8,0.8, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){-s,  s,  s,  0.9,0.9,0.9, 0,0};
	face[1] = (MeshVertex){ s,  s,  s,  0.9,0.9,0.9, 1,0};
	face[2] = (MeshVertex){ s,  s, -s,  0.9,0.9,0.9, 1,1};
	face[3] = (MeshVertex){-s,  s, -s,  0.9,0.9,0.9, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){-s, -s, -s,  0.4,0.4,0.4, 0,0};
	face[1] = (MeshVertex){ s, -s, -s,  0.4,0.4,0.4, 1,0};
	face[2] = (MeshVertex){ s, -s,  s,  0.4,0.4,0.4, 1,1};
	face[3] = (MeshVertex){-s, -s,  s,  0.4,0.4,0.4, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){ s, -s,  s,  0.7,0.7,0.7, 0,0};
	face[1] = (MeshVertex){ s, -s, -s,  0.7,0.7,0.7, 1,0};
	face[2] = (MeshVertex){ s,  s, -s,  0.7,0.7,0.7, 1,1};
	face[3] = (MeshVertex){ s,  s,  s,  0.7,0.7,0.7, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){-s, -s, -s,  0.6,0.6,0.6, 0,0};
	face[1] = (MeshVertex){-s, -s,  s,  0.6,0.6,0.6, 1,0};
	face[2] = (MeshVertex){-s,  s,  s,  0.6,0.6,0.6, 1,1};
	face[3] = (MeshVertex){-s,  s, -s,  0.6,0.6,0.6, 0,1};
	m.ops->addFace(&m, &face);

	m.ops->init(&m);
	return m;
}