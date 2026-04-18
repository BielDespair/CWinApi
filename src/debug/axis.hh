#pragma once


#include <glad/glad.h>
#include <cstdint>

#include <graphics/shapes/primitives.hh>
#include "math/Vector.hh"

GLfloat axis[] = {

    // X
    -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    // Y
    0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    // Z
    0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};


GLfloat arrows[90];
GLuint arrowsIndices[54];

void getArrowsModel(GLfloat vertices[90], GLuint indices[54]) {
    const float B = 0.1f;
    const float H = 0.5f;

    Vec3 axisList[3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    int vertexOffset = 0;

    for (int i = 0; i < 3; i++)
    {
        Vec3 dir = axisList[i];

        float tmpV[15];
        uint32_t tmpI[18];

        buildPyramid(dir, B, H, dir, tmpV, tmpI);

        Vec3 color = dir; // RGB por eixo

        for (int v = 0; v < 5; v++)
        {
            int src = v * 3;
            int dst = vertexOffset * 6;

            vertices[dst + 0] = tmpV[src + 0];
            vertices[dst + 1] = tmpV[src + 1];
            vertices[dst + 2] = tmpV[src + 2];

            vertices[dst + 3] = color.x;
            vertices[dst + 4] = color.y;
            vertices[dst + 5] = color.z;

            vertexOffset++;
        }

        for (int k = 0; k < 18; k++)
        {
            indices[i * 18 + k] = tmpI[k] + (i * 5);
        }
    }
}