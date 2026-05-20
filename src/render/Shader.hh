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
        GLuint useTextureID = 0;

        bool hasTexture = false;
        bool texturesEnabled = false;

        Shader(const std::string& vertexPath, const std::string& fragmentPath, bool hasTexture = false);

        void Delete();
        void Activate();

        void SetMat4(GLuint id, const glm::mat4& m);
        void SetVec3(GLuint id, const Vec3& v);
        void SetInt(GLuint id, int v);
        void SetBool(GLuint id, bool v);

        void texUnit(const char* uniform, GLuint unit);
        void EnableTextures();
        void DisableTextures();
};



std::string loadShaderFile(const std::string& path);