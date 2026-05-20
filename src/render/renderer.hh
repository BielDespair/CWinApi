#pragma once


#include "graphics/Mesh.hh"
#include "graphics/Texture.hh"




class Renderer {
    public:
        void Submit(Mesh* mesh, Texture* material);
        void Flush(Shader& shader, Camera& camera);




    private:
        std::unordered_map<Texture*, std::vector<Mesh*>> batches;
};