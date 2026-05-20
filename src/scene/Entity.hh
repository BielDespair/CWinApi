#pragma once

#include "graphics/Model.hh"
#include "math/transform.hh"


struct Entity {
    Transform transform;
    Model* model;

};