#pragma once

#include <unordered_map>
#include <string>

#include "graphics/Texture.hh"
#include "graphics/Model.hh"

#include "render/Shader.hh"

class ResourceManager {
    public:
        static void Init();

        static Shader* LoadShader(const std::string& vs, const std::string& fs, bool hasTexture = false);
        static Texture* LoadTexture(const std::string& image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
        static Model* LoadModel(const std::string& path);
        static void Clear();



    private:
        static inline std::unordered_map<std::string, Texture*> textures;
        static inline std::unordered_map<std::string, Shader*>  shaders;
        static inline std::unordered_map<std::string, Model*>   models;

        static inline Texture* fallbackTexture = nullptr;
        static Texture* TryLoadTexture(const std::string& path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
};