#pragma once



#include <stdint.h>
#include <cmath>
#include <glad/glad.h>

#include "math/Vector.hh"
#include "graphics/Mesh.hh"



Mesh buildPyramid(float b, float h, Vec3 c, Vec3 d, Vec3 color);



Mesh buildCylinder(float r, float h, int segments, Vec3 c, Vec3 d, Vec3 color);

