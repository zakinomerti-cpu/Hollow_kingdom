#include "mesh.h"
#include <GL/glew.h>
#include "stdio.h"
#include "stdlib.h"

static float* _tool_vertices_to_raw_array(pVoidArray* p) {
	int count = p->ops->size(p);
	float* linearArray = (float*)malloc(count*sizeof(float));

	for(int i = 0; i < count; i++) {
		linearArray[i] = *(float*)(p->data[i]);
	}
	return linearArray;
}

static GLushort* _tool_indices_to_raw_array(pVoidArray* p) {
	int count = p->ops->size(p);
	GLushort* linearArray = (GLushort*)malloc(count*sizeof(GLushort));

	for(int i = 0; i < count; i++) {
		linearArray[i] = *(GLushort*)(p->data[i]);
	}
	return linearArray;
}

static void _draw(Mesh* m) {
	if(!(m && m->isInit == 2)) return;
	glBindBuffer(GL_ARRAY_BUFFER, m->_private.vbo);
	glEnableVertexAttribArray(0); // ïîçèöèÿ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1); // öâåò
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2); // texCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->_private.ibo);
	
	unsigned int iCount = m->_private.indices.ops->size(&m->_private.indices);
	glDrawElements(GL_TRIANGLES, iCount, GL_UNSIGNED_SHORT, 0);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void _destroy(Mesh* m) {
	pVoidArray* vertices = &m->_private.vertices;
	pVoidArray* indices = &m->_private.indices;
	for(int i = 0; i < vertices->ops->size(vertices); i++) 
		free(vertices->ops->get(vertices, i));
	for(int i = 0; i < indices->ops->size(indices); i++) 
		free(indices->ops->get(indices, i));
	pVoidArrayDelete(&vertices);
	pVoidArrayDelete(&indices);
}

static void _addFace(Mesh* m, MeshVertex (*vp)[4]) {
	if(!(m->isInit == 0 || m->isInit == 1)) return;
	int floatPerVertex = sizeof(MeshVertex) / sizeof(float);
	int baseIndex = (m->_private.indices.ops->size(&m->_private.indices) / 6)*4;

	for(int i = 0; i < 4; i++) {
		float* vertexData = (float*)&((*vp)[i]);
		for(int j = 0; j < floatPerVertex; j++) {
			float* val = (float*)malloc(sizeof(float));
			*val = vertexData[j];
			m->_private.vertices.ops->add(&m->_private.vertices, val);
		}

	}

	int offset[] = {0, 1, 2, 0, 2, 3};
	for(int i = 0; i < 6; i++) {
		GLushort* idx = (GLushort*)malloc(sizeof(GLushort));
		*idx = (GLushort)(baseIndex + offset[i]);
		m->_private.indices.ops->add(&m->_private.indices, idx);
	}

	m->isInit = 1;
}

static void _init(Mesh* m) {
	if(m->isInit != 1) return;
	glGenBuffers(1, &m->_private.vbo);
	glGenBuffers(1, &m->_private.ibo);

	float* vert =  _tool_vertices_to_raw_array(&m->_private.vertices);
	GLushort* ind = _tool_indices_to_raw_array(&m->_private.indices);

	glBindBuffer(GL_ARRAY_BUFFER, m->_private.vbo);
	int vCount = m->_private.vertices.ops->size(&m->_private.vertices);
	glBufferData(GL_ARRAY_BUFFER, vCount * sizeof(float), vert, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->_private.ibo);
	int iCount = m->_private.indices.ops->size(&m->_private.indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iCount * sizeof(GLushort), ind, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	free(vert);
	free(ind);
	m->isInit = 2;
}

static const MeshInterface ops = {
	_draw,
	_destroy,
	_addFace,
	_init
};

Mesh meshCreate() {
	Mesh m = {0};
	m.isInit = 0;
	m.ops = &ops;

	//private block
	m._private.vertices = pVoidArrayCreate();
	m._private.indices = pVoidArrayCreate();
	m._private.vbo = 0;
	m._private.ibo = 0;
	return m;
}