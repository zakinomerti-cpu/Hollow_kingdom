#ifndef standart_shader
#define standart_shader

static const char* standartVertexShader =
	"#version 120\n"
	"attribute vec3 pos;\n"
	"attribute vec3 norm;\n"
	"attribute vec2 tex;\n"
	"varying vec3 vcol;\n"
	"void main() {\n"
	"	gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);\n"
	"	vcol = norm;"
	"}\n";

static const char* standartFragmentShader = 
	"#version 120\n"
	"varying vec3 texCoord;\n"
	"varying vec3 vcol;\n"
	"void main() {\n"
	"	gl_FragColor = vec4(vcol, 1.0f);\n"
	"}\n";

#endif