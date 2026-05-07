#pragma once

#include <vector>
#include <glad/glad.h>



class EBO {
    public:
        GLuint ID;

        EBO(GLuint* indices, GLsizeiptr size);
        EBO(std::vector<uint32_t>& indices);
        
        void Bind();
        void Unbind();
        void Delete();

};