#ifndef standart_shader
#define standart_shader

static const char* standartVertexShader =
	"#version 120\n"
	"attribute vec3 pos;\n"
	"attribute vec3 norm;\n"
	"attribute vec2 tex;\n"
	"varying vec3 vcol;\n"
	"varying vec2 texCoord;\n"
	"void main() {\n"
	"	gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);\n"
	"	vcol = norm;"
	"	texCoord = tex;"
	"}\n";

static const char* standartFragmentShader = 
    "#version 120\n"
    "varying vec2 texCoord;\n"
    "uniform sampler2D tex1;\n"
    "uniform sampler2D tex2;\n"
    "void main() {\n"
    "   vec3 t1 = texture2D(tex1, texCoord).rgb*4.0f;\n"
    "   vec3 t2 = texture2D(tex2, texCoord).rgb;\n"
    "   float brightness = (t2.r + t2.g + t2.b) / 3.0;\n"
    "   float mask = step(brightness, 0.1);\n"
    "   vec3 result = mix(t2, t1, mask);\n"
    "   gl_FragColor = vec4(result, 1.0);\n"
    "}\n";
#endif