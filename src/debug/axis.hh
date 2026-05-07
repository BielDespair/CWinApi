#pragma once


#include <glad/glad.h>
#include <cstdint>

#include "graphics/shapes/primitives.hh"
#include "render/Model.h"
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

Model getArrowsModel() {

    const int VERTICES_COUNT = 5;
    const int INDEX_COUNT = 18;

    const float B = 0.1f;
    const float H = 0.1f;

    Vec3 axisList[3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    
    vertices.resize(5 * 3);
    indices.resize(18 * 3); // se fixo
    

    for (size_t i = 0; i < 3; i++)
    {
        
        Vec3 dir = axisList[i];
        Mesh axisMesh = buildPyramid(B, H, dir, dir, dir);

        for (size_t j = 0; j < VERTICES_COUNT; j++)
        {
            vertices[j + (i * VERTICES_COUNT)] = axisMesh.vertices[j];
        }

        uint32_t vertexOffset = i * VERTICES_COUNT;
        for (size_t k = 0; k < INDEX_COUNT; k++)
        {
            
            indices[k + (i * INDEX_COUNT)] = axisMesh.indices[k] + vertexOffset;
        }
    }

    Mesh mesh(vertices, indices);
    Model model(mesh);
    return model;
}