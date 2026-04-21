#ifndef baseGeometry_header
#define baseGeometry_header

#include "mesh.h"
Mesh createCube(float size, float pos[3], float rot[3]);
void addCube(Mesh* m, float size, float pos[3], float rot[3]);

//Mesh createPlane(float size, float pos[3], float rot[3]);
//void addPlane(Mesh* m, float size, float pos[3], float rot[3]);

//Mesh createSphere(float size, float pos[3], float rot[3]);
//void addSphere(Mesh* m, float size, float pos[3], float rot[3]);

Mesh createHemisphere(float radius, float pos[3], float rot[3]);
//void addHalfSphere(Mesh* m, float size, float pos[3], float rot[3]);

Mesh createCircle(float radius, int segments, float pos[3], float rot[3]);
//void addCircle(Mesh* m, float size, float pos[3], float rot[3]);

#endif