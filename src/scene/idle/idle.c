#include "idle.h"
#include "scene.h"
#include <GL/gl.h>
#include <stdio.h>
#include "platform.h"
#include "shader.h"
#include "standartShader.h"
#include "baseGeometry.h"
#include "linal.h"
#include <math.h>
#include "texture.h"


static int shdInit;
static Shader shader;
static Shader shader2;
static Mesh cube;
static Mesh circle;
static TextureItem tex1;
static TextureItem tex2;
static TextureItem tex3;

static const char* standartFragmentShader2 = 
    "#version 120\n"
    "varying vec2 texCoord;\n"
    "uniform sampler2D tex3;\n"
    "void main() {\n"
    "   vec3 t1 = texture2D(tex3, texCoord).rgb;\n"
    "   gl_FragColor = vec4(t1, 1.0);\n"
    "}\n";


static void init() {
	shdInit+=1;
    float pos[3] = {0, 0, 0};
    float rot[3] = {0, 0, 0};
	cube = createHemisphere(1.0f, pos, rot);
	circle = createCircle(1.0f, 32, pos, rot);
	shader.ops->init(&shader, standartVertexShader, standartFragmentShader);
	shader2.ops->init(&shader2, standartVertexShader, standartFragmentShader2);

	//int a = 4;
	//shader.ops->setUniform(&shader, SHADER_TEX_UNIFORM, &a, 4, "int4var");
	textureItem_init(&tex1, "img/sky/sky1.jpg");
	textureItem_init(&tex2, "img/sky/sky2.jpg");
	textureItem_init(&tex3, "img/ground/grass.jpg");
}

static float angle = 0.0f;
static float posz = 0.0f;
static void _draw(SceneBucket* b, Scene* scn) {

	if(shdInit == 0) init();

	shader.ops->bind(&shader);
	

	int tex1id = tex1.ops->bind(&tex1, 0);
	shader.ops->setUniform(&shader, SHADER_TEX_UNIFORM, &tex1id, sizeof(tex1id), "tex1");

	int tex2id = tex2.ops->bind(&tex2, 1);
	shader.ops->setUniform(&shader, SHADER_TEX_UNIFORM, &tex2id, sizeof(tex2id), "tex2");

	glPushMatrix();

	glTranslatef(0.0f, -0.25f, -3.0);
	glRotatef(25, 1, 0.0, 0.0);
	angle += 0.5f;
	posz += 0.05f;

	//printf("%f\n", angle);
	angle = (angle == 360) ? 0 : angle;

	//printf("12");
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	cube.ops->draw(&cube);

	glDisable(GL_CULL_FACE);

	int tex3id = tex3.ops->bind(&tex3, 3);
	shader2.ops->setUniform(&shader2, SHADER_TEX_UNIFORM, &tex3id, sizeof(tex3id), "tex3");
	shader2.ops->bind(&shader2);
	circle.ops->draw(&circle);

	glPopMatrix();
	tex1.ops->unbind(&tex1, 1);
	tex2.ops->unbind(&tex2, 0);
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
	ShaderInit(&shader2);

	glEnable(GL_TEXTURE_2D);
	return b;
}
