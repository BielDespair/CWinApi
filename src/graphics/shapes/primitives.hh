#pragma once



#include <stdint.h>
#include <cmath>
#include <glad/glad.h>

#include "math/Vector.hh"
#include "graphics/Mesh.hh"



Mesh buildPyramid(float b, float h, Vec3 c, Vec3 d, Vec3 color);
Mesh buildCylinder(float r, float h, int segments, Vec3 c, Vec3 d, Vec3 color);
Mesh buildPlane(float w, float h, Vec3 c, Vec3 orientation);
Mesh buildCube(float size, Vec3 c);