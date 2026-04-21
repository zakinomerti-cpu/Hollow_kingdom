#include "shader.h"
#include "texture.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linal.h"
#include "hashArray.h"

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

static void _setUniform(Shader* shd, SHADERenum type, void* data, int dl, const char* name) 
{
	uniformStruct* u = malloc(sizeof(uniformStruct));
	if(!u) return;


	u->type = type;
	u->uniformLoc = 0;
	strcpy(u->name, name);
	u->data = malloc(dl);
	memcpy(u->data, data, dl);

	shd->_data->ops->add(shd->_data, u, "12");

}


static void callback1(void* p, void* args) {
	pVoidArray* arr = (pVoidArray*)args;
	arr->ops->add(arr, p);
}	


static void _bind(Shader* shd) {
	glUseProgram(shd->shaderProgram);
	int uCount = shd->_data->ops->size(shd->_data);

	pVoidArray arr = pVoidArrayCreate();
	shd->_data->ops->forEach(shd->_data, callback1, &arr);

	for(int i = 0; i < arr.ops->size(&arr); i++) {
		uniformStruct* u = arr.ops->get(&arr, i);

		if(!u->uniformLoc) {
			u->uniformLoc = glGetUniformLocation(shd->shaderProgram, u->name);
		}
		switch(u->type) {
			case SHADER_INT_UNIFORM: {
				glUniform1i(u->uniformLoc, *(int*)u->data);
			}

			case SHADER_TEX_UNIFORM: {
				glUniform1i(u->uniformLoc, *(int*)u->data);
			}

			case SHADER_FLOAT_UNIFORM: {
				glUniform1f(u->uniformLoc, *(float*)u->data);
			}
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
	//int uCount = shd->_private_block.count_of_uniforms;
	//for(int i = 0; i < uCount; i++) {
	//	
	//	uniformStruct* u = &shd->_private_block.uniformArray[i];
	//	u->uniformLoc = glGetUniformLocation(shd->shaderProgram, u->name);
	//}
	// uniform block

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}
static const ShaderInterface ops = {
	_bind,
	_unbind,
	_destroy,
	_init,

	_setUniform
};


void ShaderInit(Shader* shader) {
	shader->isInit = 0;
	shader->shaderProgram = 0;
	shader->ops = &ops;
	shader->_data = malloc(sizeof(hashArray));
	(*shader->_data) = hashArrayCreate(SHADER_UNIFORM_MAX);
}