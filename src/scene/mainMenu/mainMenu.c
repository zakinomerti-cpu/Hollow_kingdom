#include "mainMenu.h"
#include "platform.h"
#include "texture.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static TextureItem mainMenuBackground;

// ---------------- UTILS ----------------
static float frand(float a, float b) {
	return a + (float)rand() / RAND_MAX * (b - a);
}

// ---------------- TEXT ----------------
static void draw_text(float x, float y, const char* s) {
	glRasterPos2f(x, y);
	while (*s) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *s++);
}

// ---------------- GLITCH ----------------
static void draw_noise() {
	int i;
	for (i = 0; i < 25; i++) {
		float x = frand(-1,1);
		float y = frand(-1,1);
		float w = frand(0.05f,0.3f);
		float h = frand(0.01f,0.08f);

		glColor4f(frand(0,1), frand(0,1), frand(0,1), 0.15f);

		glBegin(GL_QUADS);
			glVertex2f(x,y);
			glVertex2f(x+w,y);
			glVertex2f(x+w,y+h);
			glVertex2f(x,y+h);
		glEnd();
	}
}

// ---------------- DRAW (IMPORTANT: NO render() CALLS HERE) ----------------
static void _draw(SceneBucket* b, Scene* scn) {

    glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(0,0,-2);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// background
	glColor3f(0.03f, 0.03f, 0.05f);
	glBegin(GL_QUADS);
		glVertex2f(-1,-1);
		glVertex2f( 1,-1);
		glVertex2f( 1, 1);
		glVertex2f(-1, 1);
	glEnd();

	// texture layer
	mainMenuBackground.ops->bind(&mainMenuBackground, 0);
	glColor4f(1,1,1,0.2f);

	glBegin(GL_QUADS);
		glTexCoord2f(0,1); glVertex2f(-1,-1);
		glTexCoord2f(1,1); glVertex2f( 1,-1);
		glTexCoord2f(1,0); glVertex2f( 1, 1);
		glTexCoord2f(0,0); glVertex2f(-1, 1);
	glEnd();

	mainMenuBackground.ops->unbind(&mainMenuBackground, 0);

	// glitch layer
	draw_noise();

	// title
	glColor3f(0.8f,1.0f,0.4f);
	draw_text(-0.8f, 0.77f, "HOLLOW KINGDOM");
	draw_text(-0.8f, 0.73f, "MAIN MENU / STABLE=FALSE");
	draw_text(-0.8f, -0.8, "TO RUN GAME PRESS A, TO EXIT PRESS E");
	
	glPopMatrix();
    glPopAttrib();
}

static int _process(SceneBucket* b, Scene* scn) {
	unsigned char keys[256] = {0};
	scn->plt->getPressedKeys(scn->plt, &keys);


	if(keys['a']) {
		return 1;
	}
		
	if(keys['e']) {
		return -1;
	}
	
	return 0;
}

static void _destroy() {

}

static const SceneBucketInterface ops = {
	_process,
	_draw,
	_destroy
};

// ---------------- INIT ----------------
SceneBucket mainMenuScene() {
	SceneBucket menu;
	menu.ops = &ops;
	menu.isInit = 1;

	textureItem_init(&mainMenuBackground,
					 "img/background/background.bmp");

	srand((unsigned)time(NULL));

	return menu;
}


