#pragma once


#include <vector>

#include <glad/glad.h>

#include "graphics/Vertex.hh"


class VBO {
    public:
        GLuint ID;

        VBO(GLfloat* vertices, GLsizeiptr size);
        VBO(const std::vector<Vertex>& vertices);
        
        void Bind();
        void Unbind();
        void Delete();

};