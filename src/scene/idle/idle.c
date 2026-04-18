#include "idle.h"
#include "scene.h"
#include <GL/gl.h>
#include <stdio.h>
#include "platform.h"
#include "shader.h"
#include "standartShader.h"
#include "baseGeometry.h"


static int shdInit;
static Shader shader;
static Mesh cube;

static void init() {
	shdInit+=1;
    float pos[3];
    float rot[3];
	cube = createCube(1.0f, pos, rot);
	shader.ops->init(&shader, standartVertexShader, standartFragmentShader);
}

static float angle = 0.0f;
static void _draw(SceneBucket* b, Scene* scn) {

	if(shdInit == 0) init();

	shader.ops->bind(&shader);
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(angle, 0, 1.0, 1.0);
	angle += 0.5f;

	//printf("12");
	
	cube.ops->draw(&cube);

	glPopMatrix();
	shader.ops->unbind(&shader);

}

static int _process(SceneBucket* b, Scene* scn) {
	unsigned char keys[256] = {0};
	scn->plt->getPressedKeys(scn->plt, &keys);
		
	if(keys['q']) {
		return -1;
	}

	if(keys['m']) {
		return -2;
	}

	return 0;
}
static void _destroy(SceneBucket* b) {
	
}

static const SceneBucketInterface ops = {
	_process,
	_draw,
	_destroy
};


SceneBucket idleScene() {
	SceneBucket b;
	b.ops = &ops;
	b.isInit = 1;

	shdInit = 0;
	ShaderInit(&shader);
	return b;
}
