#pragma once

#include <vector>


#include "graphics/Camera.hh"

#include "Vertex.hh"
#include "render/Shader.hh"

#include "render/buffers/VAO.hh"
#include "render/buffers/EBO.hh"
#include "render/buffers/VBO.hh"



class Mesh {
    public:


        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;


        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
        void Draw(Shader&, Camera& camera);
    private:
        VAO VAO;
};