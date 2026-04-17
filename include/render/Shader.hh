#pragma once

#include <fstream>
#include <sstream>

#include <glad/glad.h>

class Shader {
public:
    GLuint ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void Delete();
    
    void Activate();

};



std::string loadShaderFile(const std::string& path);