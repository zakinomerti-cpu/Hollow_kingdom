#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GLuint createShader(GLenum type, const char* src) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, 0);
	glCompileShader(shader);

	int success;
	char log[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, 1024, NULL, log);
		printf("%s\n", log);
		return 0;
	}

	return shader;
}

static void _setFloatUniform(Shader* shd, const char* name, float value) {
	uniformStruct u;
	u.type = SHADER_FLOAT_UNIFORM;
	strcpy(u.name, name);
	u.data = malloc(sizeof(float));
	*(float*)u.data = value;
	u.uniformLoc = 0;

	int index = 0;
	int* uCount = &shd->_private_block.count_of_uniforms;
	for(int i = 0; i < (*uCount); i++) {
		char* uName =  shd->_private_block.uniformArray[i].name;
		if(strcmp(uName, name) == 0) {
			index = i;
		}
	}

	if(index == 0) {
		index = (*uCount);
		(*uCount)++;
	}
	shd->_private_block.uniformArray[index] = u;

}
static void _setVec2Uniform(Shader* shd, const char* name, vec2 v) {}
static void _setVec3Uniform(Shader* shd, const char* name, vec3 v) {}
static void _setVec4Uniform(Shader* shd, const char* name, vec4 v) {}
static void _setMat4Uniform(Shader* shd, const char* name, mat4 m) {
	uniformStruct u;
	u.type = SHADER_MAT4_UNIFORM;
	strcpy(u.name, name);
	u.data = malloc(sizeof(mat4));
	*(mat4*)u.data = m;
	u.uniformLoc = 0;

	int index = 0;
	int* uCount = &shd->_private_block.count_of_uniforms;
	for(int i = 0; i < (*uCount); i++) {
		char* uName =  shd->_private_block.uniformArray[i].name;
		if(strcmp(uName, name) == 0) {
			index = i;
		}
	}

	if(index == 0) {
		index = (*uCount);
		(*uCount)++;
	}
	shd->_private_block.uniformArray[index] = u;
}
static void _setTextureUniform(Shader* shd, const char* name, TextureItem* tx) {}

static void _getFloatUniform(Shader* shd, const char* name, float* value) {}
static void _getVec2Uniform(Shader* shd, const char* name, vec2* v) {}
static void _getVec3Uniform(Shader* shd, const char* name, vec3* v) {}
static void _getVec4Uniform(Shader* shd, const char* name, vec4* v) {}
static void _getMat4Uniform(Shader* shd, const char* name, mat4* m) {}
static void _getTextureUniform(Shader* shd, const char* name, TextureItem* tx) {}


static void _bind(Shader* shd) {
	glUseProgram(shd->shaderProgram);
	int uCount = shd->_private_block.count_of_uniforms;
	for(int i = 0; i < uCount; i++) {
		
		uniformStruct* u = &shd->_private_block.uniformArray[i];
		switch(u->type) {
			case SHADER_NONE_UNIFORM:
				break;

			case SHADER_FLOAT_UNIFORM:
				glUniform1f(u->uniformLoc, *(float*)u->data);
				break;

			case SHADER_VEC2_UNIFORM:
				break;

			case SHADER_VEC3_UNIFORM:
				break;

			case SHADER_VEC4_UNIFORM:
				break;

			case SHADER_MAT4_UNIFORM:
				glUniformMatrix4fv(u->uniformLoc, 1, GL_TRUE, ((mat4*)u->data)->m);
				break;

			case SHADER_TEX_UNIFORM:
				break;
		}
	}
}
static void _unbind(Shader* shd) {
	glUseProgram(0);
}
static void _destroy(Shader* shd) {}
static void _init(Shader* shd, const char* vert, const char* frag) {


	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vert);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, frag);
	shd->shaderProgram = glCreateProgram();
	
	// attribute block
	glBindAttribLocation(shd->shaderProgram, 0, "pos");
	glBindAttribLocation(shd->shaderProgram, 1, "norm");
	glBindAttribLocation(shd->shaderProgram, 2, "tex");
	// attribute block

	glAttachShader(shd->shaderProgram, vertexShader);
	glAttachShader(shd->shaderProgram, fragmentShader);
	glLinkProgram(shd->shaderProgram);


	// uniform block
	int uCount = shd->_private_block.count_of_uniforms;
	for(int i = 0; i < uCount; i++) {
		
		uniformStruct* u = &shd->_private_block.uniformArray[i];
		u->uniformLoc = glGetUniformLocation(shd->shaderProgram, u->name);
	}
	// uniform block

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}
static const ShaderInterface ops = {
	_bind,
	_unbind,
	_destroy,
	_init,

	_setFloatUniform,
	_setVec2Uniform,
	_setVec3Uniform,
	_setVec4Uniform,
	_setMat4Uniform,
	_setTextureUniform,

	_getFloatUniform,
	_getVec2Uniform,
	_getVec3Uniform,
	_getVec4Uniform,
	_getMat4Uniform,
	_getTextureUniform
};


void ShaderInit(Shader* shader) {
	shader->isInit = 0;
	shader->shaderProgram = 0;
	shader->ops = &ops;

	shader->_private_block.count_of_uniforms = 0;
	for(int i = 0; i < SHADER_UNIFORM_MAX; i++) {
		shader->_private_block.uniformArray[i].uniformLoc = 0;
		shader->_private_block.uniformArray[i].type = SHADER_NONE_UNIFORM;
		memset(shader->_private_block.uniformArray[i].name, 0, sizeof(char)*32);
		shader->_private_block.uniformArray[i].data = NULL;
	}
}