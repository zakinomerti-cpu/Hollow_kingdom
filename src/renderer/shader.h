#ifndef shader_header
#define shader_header

#define SHADER_UNIFORM_MAX 64

#include "hashArray.h"

struct Shader;
struct TextureItem;

typedef enum {
	SHADER_INT_UNIFORM,
	SHADER_NONE_UNIFORM,
	SHADER_FLOAT_UNIFORM,
	SHADER_VEC2_UNIFORM,
	SHADER_VEC3_UNIFORM,
	SHADER_VEC4_UNIFORM,
	SHADER_MAT2_UNIFORM,
	SHADER_MAT3_UNIFORM,
	SHADER_MAT4_UNIFORM,
	SHADER_TEX_UNIFORM,
} SHADERenum;

typedef struct uniformStruct {
	SHADERenum type;
	int uniformLoc;
	char name[32];
	void* data;
} uniformStruct;

typedef struct ShaderInterface {
	void (*bind)(struct Shader*);
	void (*unbind)(struct Shader*);
	void (*destroy)(struct Shader*);
	void (*init)(struct Shader*, const char* vert, const char* frag);

	// копирует значение по адресу
	void (*setUniform)(struct Shader*, SHADERenum type, void* data, int dl, const char* name);

} ShaderInterface;

typedef struct Shader {
	char isInit;
	unsigned int shaderProgram;
	const ShaderInterface* ops;
	struct hashArray* _data;
} Shader;

void ShaderInit(struct Shader* shader);

#endif