#include "baseGeometry.h"
#include <stdlib.h>
#include <math.h>

// создает законченную геометрию
Mesh createCube(float size, float pos[3], float rot[3]) {
	Mesh m = meshCreate();
	float s = size / 2.0f;
	MeshVertex face[4];

	face[0] = (MeshVertex){-s, -s,  s,  0,0,1, 0,0};
	face[1] = (MeshVertex){ s, -s,  s,  0,0,1, 1,0};
	face[2] = (MeshVertex){ s,  s,  s,  0,0,1, 1,1};
	face[3] = (MeshVertex){-s,  s,  s,  0,0,1, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){ s, -s, -s,  0,0,-1, 0,0};
	face[1] = (MeshVertex){-s, -s, -s,  0,0,-1, 1,0};
	face[2] = (MeshVertex){-s,  s, -s,  0,0,-1, 1,1};
	face[3] = (MeshVertex){ s,  s, -s,  0,0,-1, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){-s,  s,  s,  0,1,0, 0,0};
	face[1] = (MeshVertex){ s,  s,  s,  0,1,0, 1,0};
	face[2] = (MeshVertex){ s,  s, -s,  0,1,0, 1,1};
	face[3] = (MeshVertex){-s,  s, -s,  0,1,0, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){-s, -s, -s,  0,-1,0, 0,0};
	face[1] = (MeshVertex){ s, -s, -s,  0,-1,0, 1,0};
	face[2] = (MeshVertex){ s, -s,  s,  0,-1,0, 1,1};
	face[3] = (MeshVertex){-s, -s,  s,  0,-1,0, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){ s, -s,  s,  1,0,0, 0,0};
	face[1] = (MeshVertex){ s, -s, -s,  1,0,0, 1,0};
	face[2] = (MeshVertex){ s,  s, -s,  1,0,0, 1,1};
	face[3] = (MeshVertex){ s,  s,  s,  1,0,0, 0,1};
	m.ops->addFace(&m, &face);

	face[0] = (MeshVertex){-s, -s, -s,  -1,0,0, 0,0};
	face[1] = (MeshVertex){-s, -s,  s,  -1,0,0, 1,0};
	face[2] = (MeshVertex){-s,  s,  s,  -1,0,0, 1,1};
	face[3] = (MeshVertex){-s,  s, -s,  -1,0,0, 0,1};
	m.ops->addFace(&m, &face);

	m.ops->init(&m);
	return m;
}

// создает полусферу (8 сегментов по горизонтали, 4 по вертикали)
Mesh createHemisphere(float radius, float pos[3], float rot[3]) {
    Mesh m = meshCreate();
    
    int radialSegments = 32;   // линии по вертикали (меридианы)
    int heightSegments = 16;   // линии по горизонтали (параллели)
    
    // массив для хранения всех вершин
    MeshVertex vertices[heightSegments+1][radialSegments+1]; // (heightSegments+1) x (radialSegments+1)
    
    // генерация вершин
    for (int i = 0; i <= heightSegments; i++) {
        float phi = 1.57079632679f * i / heightSegments; // π/2 = 1.57079632679
        float rY = radius * sinf(phi);
        float rXY = radius * cosf(phi);
        float v = 1.0f - (float)i / heightSegments;
        
        for (int j = 0; j <= radialSegments; j++) {
            float theta = 6.28318530718f * j / radialSegments; // 2π = 6.28318530718
            float x = rXY * cosf(theta);
            float z = rXY * sinf(theta);
            float y = rY;
            
            // нормаль
            float nx = x / radius;
            float ny = y / radius;
            float nz = z / radius;
            
            // UV
            float u = (float)j / radialSegments;
            
            vertices[i][j] = (MeshVertex){x, y, z, nx, ny, nz, u, v};
        }
    }
    
    // создание граней
    MeshVertex face[4];
    
    for (int i = 0; i < heightSegments; i++) {
        for (int j = 0; j < radialSegments; j++) {
            face[0] = vertices[i][j];
            face[1] = vertices[i][j+1];
            face[2] = vertices[i+1][j+1];
            face[3] = vertices[i+1][j];
            m.ops->addFace(&m, &face);
        }
    }
    
    m.ops->init(&m);
    return m;
}

// создает круг (многоугольник) с возможностью выбора количества точек
// текстурные координаты: круг вписан в квадрат [0,1] x [0,1], центр в (0.5, 0.5)
Mesh createCircle(float radius, int segments, float pos[3], float rot[3]) {
    Mesh m = meshCreate();
    
    if (segments < 3) segments = 3;  // минимум треугольник
    
    // массив для хранения всех вершин (центр + точки окружности)
    MeshVertex* vertices = (MeshVertex*)malloc((segments + 1) * sizeof(MeshVertex));
    
    // центр круга (вершина 0)
    // UV координаты: центр текстуры (0.5, 0.5)
    vertices[0] = (MeshVertex){
        0.0f, 0.0f, 0.0f,  // позиция
        0.0f, 1.0f, 0.0f,  // нормаль (смотрим вверх)
        0.5f, 0.5f         // текстурные координаты (центр)
    };
    
    // генерация вершин на окружности
    for (int i = 0; i < segments; i++) {
        float angle = 6.28318530718f * i / segments; // 2π * i / segments
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        
        // UV: преобразуем координаты [-radius, radius] в [0, 1]
        // центр круга (0,0) -> (0.5, 0.5)
        // край круга (radius, 0) -> (1, 0.5)
        float u = (x / radius) * 0.5f + 0.5f;
        float v = (z / radius) * 0.5f + 0.5f;
        
        vertices[i + 1] = (MeshVertex){
            x, 0.0f, z,      // позиция
            0.0f, 1.0f, 0.0f, // нормаль
            u, v              // текстурные координаты
        };
    }
    
    // создание вырожденных четырехугольников (треугольников)
    // Формат: [центр, вершина_i, вершина_{i+1}, вершина_{i+1}]
    MeshVertex face[4];
    
    for (int i = 0; i < segments; i++) {
        int next = (i + 1) % segments;
        
        face[0] = vertices[0];           // центр
        face[1] = vertices[i + 1];       // текущая вершина на окружности
        face[2] = vertices[next + 1];    // следующая вершина на окружности
        face[3] = vertices[next + 1];    // дублируем последнюю вершину (вырожденный четырехугольник)
        
        m.ops->addFace(&m, &face);
    }
    
    free(vertices);
    m.ops->init(&m);
    return m;
}