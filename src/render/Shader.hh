#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>

#include "math/Vector.hh"

class Shader {
public:
    GLuint ID;
    Shader(const std::string& vertexPath, const std::string& fragmentPath);


    void Delete();
    void Activate();

    void SetMat4(GLuint id, const glm::mat4& m);
    void SetVec3(GLuint id, const Vec3& v);
    void SetInt(GLuint id, int v);
};



std::string loadShaderFile(const std::string& path);