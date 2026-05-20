#include "Scene.hh"

Scene::Scene(Camera& camera, Input& input, Renderer& renderer) : camera(camera), input(input), renderer(renderer) {
    
    //Model* myCube = ResourceManager::LoadModel("assets/models/gobul.obj");





}

void Scene::Update(float dt) {
    
    camera.Update(dt);
    HandleActions();

    entityController.Update(selected, input, dt);
}

void Scene::Render() {
    
}



void Scene::HandleActions()
{

    if (input.IsActionPressed(Action::Debug)) {
        debug = !debug;
        std::cout << "Debug: " << debug << std::endl;

        camera.Reset();

        if (selected != nullptr) {
            selected->transform.Reset();
        }
    }
}