#define STB_IMAGE_IMPLEMENTATION
#include <GL/gl.h>
#include <GL/glu.h>
#include "texture.h"
#include "stb/stb_image.h"

static GLuint _create(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    
    if (!data) {
        printf("Ошибка загрузки текстуры: %s\n", stbi_failure_reason());
        return 0;
    }
    
    // Проверка размеров для OpenGL 1.1
    int w = width, h = height;
    
    // Проверка степени двойки
    if ((w & (w - 1)) != 0 || (h & (h - 1)) != 0) {
        printf("Предупреждение: размеры текстуры %dx%d не являются степенью двойки\n", w, h);

    }
    
    GLuint tex_id;
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, 
                 format, GL_UNSIGNED_BYTE, data);
    
    stbi_image_free(data);
    return tex_id;
}

static void _bind(TextureItem* tx) {
	if(tx && tx->id) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tx->id);
	}
}
static void _unbind(TextureItem* tx) {
	if(tx && tx->id) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
static void _destroy(TextureItem* tx) {
	if(tx && tx->id) {
		glDeleteTextures(1, &tx->id);
		tx->id = 0;
	}
}

static TextureItemInterface ops = {
	_bind,
	_unbind,
	_destroy
};

void textureItem_init(TextureItem* tx, const char* path) {
	if(!tx || !path) return;
	tx->id = _create(path);
	tx->ops = &ops;
}