#pragma once

#include <math/constants.hh>

#include "scene/Entity.hh"
#include "input/input.hh"











class EntityController {
    public:

        void Update(Entity* entity, const Input& input, float dt);

    private:
        float rotSpeed = 0.005f; // rad/s
};