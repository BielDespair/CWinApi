#pragma once


#include <glad/glad.h>
#include <cstdint>

#include "graphics/shapes/primitives.hh"
#include "graphics/Model.hh"
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

    const float B = 0.1f;
    const float H = 0.1f;

    Vec3 axisList[3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    std::vector<Mesh> meshes;
        
    for (size_t i = 0; i < 3; i++)
    {
        
        Vec3 dir = axisList[i];
        Mesh axisMesh = buildPyramid(B, H, dir, dir, dir);
        meshes.push_back(axisMesh);
    }

    Model model(meshes);
    return model;
}