#pragma once

#include <vector>

#include "resources/ResourceManager.hh"

#include "render/Renderer.hh"
#include "Entity.hh"
#include "Camera.hh"


#include "controller/EntityController.hh"



class Scene {
    public:

        Renderer& renderer;
        Camera& camera;
        Input& input;


        Entity* selected = nullptr;
        std::vector<Entity> entities;


        bool debug = false;


        Scene(Camera& camera, Input& input, Renderer& renderer);
        void Update(float dt);
        void Render();
        
        
    private:
        void HandleActions();
        EntityController entityController;

};