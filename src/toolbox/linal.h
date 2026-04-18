#ifndef linal_header
#define linal_header

#include <math.h>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

typedef struct mat4 { float m[16]; } mat4;
typedef struct vec2 { float x; float y; } vec2;
typedef struct vec3 { float x; float y; float z; } vec3;
typedef struct vec4 { float x; float y; float z; float w; } vec4;



// mat4 block
static inline mat4 matIdentity() {
    mat4 m = {0}; m.m[0]=m.m[5]=m.m[10]=m.m[15]=1; return m;
}
static inline mat4 matTranslation(float x,float y,float z) {
    mat4 m=matIdentity(); m.m[3]=x; m.m[7]=y; m.m[11]=z; return m;
}
static inline mat4 matRotationX(float a) {
    mat4 m=matIdentity(); float c=cosf(a), s=sinf(a);
    m.m[5]=c; m.m[6]=-s; m.m[9]=s; m.m[10]=c; return m;
}
static inline mat4 matRotationY(float a) {
    mat4 m=matIdentity(); float c=cosf(a), s=sinf(a);
    m.m[0]=c; m.m[2]=s; m.m[8]=-s; m.m[10]=c; return m;
}
static inline mat4 matRotationZ(float a) {
    mat4 m=matIdentity(); float c=cosf(a), s=sinf(a);
    m.m[0]=c; m.m[1]=-s; m.m[4]=s; m.m[5]=c; return m;
}
static inline mat4 matScale(float x,float y,float z) {
    mat4 m=matIdentity(); m.m[0]=x; m.m[5]=y; m.m[10]=z; return m;
}
static inline mat4 matPerspective(float fovDeg,float aspect,float znear,float zfar) {
    mat4 m={0}; float f=tanf((fovDeg*M_PI/180.0f)*0.5f);
    m.m[0]=1.0f/(aspect*f); m.m[5]=1.0f/f;
    m.m[10]=-(zfar+znear)/(zfar-znear);
    m.m[11]=-(2.0f*zfar*znear)/(zfar-znear);
    m.m[14]=-1.0f; return m;
}
static inline mat4 matMultiply(mat4 a, mat4 b) {
    mat4 m={0};
    for(int i=0;i<4;++i) for(int j=0;j<4;++j) {
        float sum=0; for(int k=0;k<4;++k) sum+=a.m[i*4+k]*b.m[k*4+j];
        m.m[i*4+j]=sum;
    }
    return m;
}


//vec2 block
static inline vec2 vec2Create(float x, float y) {
	vec2 v = {0}; v.x = x; v.y = y; return v;
}
static inline vec2 vec2Mul(vec2 x, vec2 y) {
	vec2 v = {0}; v.x = x.x * y.x; v.y = x.y * y.y; return v;
}
static inline vec2 vec2Div(vec2 x, vec2 y) {
	vec2 v = {0}; v.x = x.x / y.x; v.y = x.y / y.y; return v;
}
static inline vec2 vec2Add(vec2 x, vec2 y) {
	vec2 v = {0}; v.x = x.x + y.x; v.y = x.y + y.y; return v;
}
static inline vec2 vec2Sub(vec2 x, vec2 y) {
	vec2 v = {0}; v.x = x.x - y.x; v.y = x.y - y.y; return v;
}
static inline float vec2Length(vec2 v) {
	return sqrtf(v.x*v.x + v.y*v.y);
}
static inline vec2 vec2Norm(vec2 a) {
	vec2 v = {0};
	float l = vec2Length(a);
	v.x = (l > 0) ? a.x / l : 0.0;
	v.y = (l > 0) ? a.y / l : 0.0;
	return v;
}



//vec3 block
static inline vec3 vec3Create(float x, float y, float z) {
	vec3 v = {0}; v.x = x; v.y = y; v.z = z; return v;
}
static inline vec3 vec3Mul(vec3 a, vec3 b) {
	vec3 v = {0}; v.x = a.x * b.x; v.y = a.y * b.y; v.z = a.z * b.z; return v;
}
static inline vec3 vec3Div(vec3 a, vec3 b) {
	vec3 v = {0}; v.x = a.x / b.x; v.y = a.y / b.y; v.z = a.z / b.z; return v;
}
static inline vec3 vec3Add(vec3 a, vec3 b) {
	vec3 v = {0}; v.x = a.x + b.x; v.y = a.y + b.y; v.z = a.z + b.z; return v;
}
static inline vec3 vec3Sub(vec3 a, vec3 b) {
	vec3 v = {0}; v.x = a.x - b.x; v.y = a.y - b.y; v.z = a.z - b.z; return v;
}
static inline float vec3Length(vec3 v) {
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}
static inline vec3 vec3Norm(vec3 a) {
	vec3 v = {0};
	float l = vec3Length(a);
	v.x = (l > 0) ? a.x / l : 0.0;
	v.y = (l > 0) ? a.y / l : 0.0;
	v.z = (l > 0) ? a.z / l : 0.0;
	return v;
}



//vec4 block
static inline vec4 vec4Create(float x, float y, float z, float w) {
	vec4 v = {0}; v.x = x; v.y = y; v.z = z; v.w = w; return v;
}
static inline vec4 vec4Mul(vec4 a, vec4 b) {
	vec4 v = {0}; v.x = a.x * b.x; v.y = a.y * b.y; v.z = a.z * b.z;  v.w = a.w * b.w; return v;
}
static inline vec4 vec4Div(vec4 a, vec4 b) {
	vec4 v = {0}; v.x = a.x / b.x; v.y = a.y / b.y; v.z = a.z / b.z;  v.w = a.w / b.w; return v;
}
static inline vec4 vec4Add(vec4 a, vec4 b) {
	vec4 v = {0}; v.x = a.x + b.x; v.y = a.y + b.y; v.z = a.z + b.z;  v.w = a.w + b.w; return v;
}
static inline vec4 vec4Sub(vec4 a, vec4 b) {
	vec4 v = {0}; v.x = a.x - b.x; v.y = a.y - b.y; v.z = a.z - b.z;  v.w = a.w - b.w; return v;
}
static inline float vec4Length(vec4 v) {
	return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
}
static inline vec4 vec4Norm(vec4 a) {
	vec4 v = {0};
	float l = vec4Length(a);
	v.x = (l > 0) ? a.x / l : 0.0;
	v.y = (l > 0) ? a.y / l : 0.0;
	v.z = (l > 0) ? a.z / l : 0.0;
	v.w = (l > 0) ? a.w / l : 0.0;
	return v;
}

#endif