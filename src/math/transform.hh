#pragma once

#include <math/constants.hh>
#include <glm/ext/matrix_float4x4.hpp>


#include "Vector.hh"




struct Transform {
    Vec3 position = { 0.0f };
    Vec3 rotation = { 0.0f };
    Vec3 scale = { 1.0f };

    glm::mat4 toMatrix();

    void AddRotation(Vec3 delta);
    void ScaleBy(Vec3 factor);

    void SetPosition(Vec3 p);
    void SetRotation(Vec3 r);
    
    void NormalizeRotation();
    void Reset();
};  