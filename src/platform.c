#include "platform.h"
#include <stdlib.h>
#include <stdio.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <string.h>

static unsigned char click;
static int mousePosX, mousePosY;

static unsigned char keys[256];
//static gameState* g_gs;

void(*displayFunc)(void) = NULL;
char shouldClose_ = 0;

//privateFunc
void onClose() {
    shouldClose_ = 1;
    //g_gs->shouldClose = 1;
}

static void keyboard(unsigned char key, int x, int y) {
    keys[key] = 1;
}

static void keyboard_up(unsigned char key, int x, int y) {
    keys[key] = 0;  // для release (glutKeyboardUpFunc)
}

static void mouseMotion(int x, int y) {
    mousePosX = x;
	mousePosY = y;
}

static void _getPressedKeys(platform* p, unsigned char (*in_keys)[256]) {
    memcpy(in_keys, keys, sizeof(char)*256);
}

static void mouseButton(int button, int state, int x, int y)
{
    // button: GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
    // state: GLUT_DOWN / GLUT_UP

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        click = 1;
    }
	else {
		click = 0;
	}
}

static unsigned char clickRet(platform* plt) {
	return click;
}

static void getMousePos(platform* plt, int* mx, int* my) {
	(*mx) = mousePosX;
	(*my) = mousePosY;
}

void privateDisplayFunc() {

    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(displayFunc)
    displayFunc();

    glutSwapBuffers();
    glutPostRedisplay();
}

void platformInit(platform* plt) {
    glewInit();
    glutDisplayFunc(privateDisplayFunc);
    if (plt->startFunc)
        plt->startFunc();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);  // optional
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
    glutCloseFunc(onClose);

}
void render(platform* plt) {
    glutMainLoopEvent();
    //memcpy(plt->gs->key, keys, sizeof(byte)*256);
}
void setStartFunc(platform* plt, void (*func)(void)) {
    plt->startFunc = func;
}
void setDisplayFunc(platform* plt, void (*func)(void)) {
    displayFunc = func;
}
unsigned char shouldClose(platform* plt) {
    return shouldClose_;
}

void createWindow(platform* plt, const char* title, int w, int h) {
    glutInitWindowSize(w, h);
    glutCreateWindow(title);
}

platform* Glutplatform_new(int argc, char** argv) {
    platform* plt = (platform*)malloc(sizeof(platform));
    if (!plt) return NULL;
        
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    plt->render = render;
    plt->platformInit = platformInit;
    plt->setStartFunc = setStartFunc;
    plt->setDisplayFunc = setDisplayFunc;

    plt->createWindow = createWindow;
    plt->shouldClose = shouldClose;

    //plt->gs = gs;
    shouldClose_ = 0;

    plt->startFunc = NULL;
    return plt;
}

void glutPlatform_init(platform* plt, int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    plt->render = render;
    plt->platformInit = platformInit;
    plt->setStartFunc = setStartFunc;
    plt->setDisplayFunc = setDisplayFunc;

    plt->createWindow = createWindow;
    plt->shouldClose = shouldClose;
	plt->getMousePos = getMousePos;
	plt->click = clickRet;

    plt->getPressedKeys = _getPressedKeys;

    //g_gs = gs;
    //plt->gs = gs;
    shouldClose_ = 0;

    //memset(keys, 0, sizeof(byte)*256);

    plt->startFunc = NULL;
}