#pragma once


#include "Texture.hh"






struct Material {
    Texture* albedo = nullptr;
    Texture* normal = nullptr;
    Texture* specular = nullptr;

    bool useVertexColor = true;
};