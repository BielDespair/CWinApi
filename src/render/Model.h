#pragma once

#include "graphics/Mesh.hh"
#include "graphics/Camera.hh"

#include "Shader.hh"



class Model {
    public:

        Model(Mesh& mesh);
        Model(const char* filePath);
        void Draw(Shader& shader, Camera& camera);

    private:
        std::vector<Mesh> meshes;        
};