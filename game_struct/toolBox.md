```c
#ifndef toolbox_header
#define toolbox_header

typedef unsigned char byte;

typedef struct {
	byte c[3];
} color;

typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
	float x;
	float y;
	float z;
} vec3;

color createColor(int r, int g, int b);

vec2 vec2Create(float x, float y);
vec2 vec2Add(vec2 a, vec2 b);
vec2 vec2Sub(vec2 a, vec2 b);
vec2 vec2Mul(vec2 a, vec2 b);
vec2 vec2Div(vec2 a, vec2 b);

vec3 vec3Create(float x, float y, float z);
vec3 vec3Add(vec3 a, vec3 b);
vec3 vec3Sub(vec3 a, vec3 b);
vec3 vec3Mul(vec3 a, vec3 b);
vec3 vec3Div(vec3 a, vec3 b);

#endif

```