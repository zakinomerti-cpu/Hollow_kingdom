#ifndef shader_header
#define shader_header

#include "linal.h"
#define SHADER_UNIFORM_MAX 64

struct Shader;
struct TextureItem;

typedef enum {
	SHADER_NONE_UNIFORM,
	SHADER_FLOAT_UNIFORM,
	SHADER_VEC2_UNIFORM,
	SHADER_VEC3_UNIFORM,
	SHADER_VEC4_UNIFORM,
	SHADER_MAT4_UNIFORM,
	SHADER_TEX_UNIFORM,
} SHADERenum;

typedef struct uniformStruct {
	int uniformLoc;
	SHADERenum type;
	char name[32];
	void* data;
} uniformStruct;

typedef struct ShaderInterface {
	void (*bind)(struct Shader*);
	void (*unbind)(struct Shader*);
	void (*destroy)(struct Shader*);
	void (*init)(struct Shader*, const char* vert, const char* frag);

	void (*setFloatUniform)(struct Shader*, const char* name, float value);
	void (*setVec2Uniform)(struct Shader*, const char* name, vec2 v);
	void (*setVec3Uniform)(struct Shader*, const char* name, vec3 v);
	void (*setVec4Uniform)(struct Shader*, const char* name, vec4 v);
	void (*setMat4Uniform)(struct Shader*, const char* name, mat4 m);
	void (*setTextureUniform)(struct Shader*, const char* name, struct TextureItem*);

	void (*getFloatUniform)(struct Shader*, const char* name, float* value);
	void (*getVec2Uniform)(struct Shader*, const char* name, vec2* v);
	void (*getVec3Uniform)(struct Shader*, const char* name, vec3* v);
	void (*getVec4Uniform)(struct Shader*, const char* name, vec4* v);
	void (*getMat4Uniform)(struct Shader*, const char* name, mat4* m);
	void (*getTextureUniform)(struct Shader*, const char* name, struct TextureItem*);

} ShaderInterface;

typedef struct ShaderPrivate {
	int count_of_uniforms;
	uniformStruct uniformArray[SHADER_UNIFORM_MAX];
} ShaderPrivate;




// how to create Shader object?
// 1) Shader shader = {0};
// 2) ShaderInit(shader, vShaderPath, fShaderPath);
// 3) shader->setFloatUniform(&shader, "uniform1", 1.0f);
// 4) shader->init(&shader);
// end
//
// how to use Shader object?
// 1) create
// 2) shader->bind(&shader);
// 3) shader->unbind(^shader);
// end
//
// how to reset uniform? ( 64 uniforms max )
// 1) shader->setFloatUniform(&shader, "uniform1", 1.0f); // create uniform "uniform1"
// 2) shader->setFloatUniform(&shader, "uniform1", 33.0f); // change value of "uniform1"
// end
//
//how to delete Shader object?
// 1) shader->destroy();
// end
typedef struct Shader {
	char isInit;
	unsigned int shaderProgram;
	const ShaderInterface* ops;
	ShaderPrivate _private_block;
} Shader;

void ShaderInit(struct Shader* shader);

#endif