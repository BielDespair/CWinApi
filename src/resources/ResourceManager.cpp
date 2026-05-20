#include "ResourceManager.hh"

void ResourceManager::Init() {

    stbi_set_flip_vertically_on_load(true);

    fallbackTexture = new Texture(
        "assets/textures/missing.jpg",
        GL_TEXTURE_2D, GL_TEXTURE0,
        GL_RGB, GL_UNSIGNED_BYTE);
}

Texture *ResourceManager::LoadTexture(const std::string& path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    auto it = textures.find(path);
    if (it != textures.end())
        return it->second;

    Texture* tex = TryLoadTexture(path, texType, slot, format, pixelType);
    textures[path] = tex;
    return tex;
}

Shader *ResourceManager::LoadShader(const std::string &vs, const std::string &fs, bool hasTexture) {
    std::string key = vs + "|" + fs;

    auto it = shaders.find(key);
    if (it != shaders.end())
        return it->second;

    Shader* s = new Shader(vs.c_str(), fs.c_str(), hasTexture);
    shaders[key] = s;
    return s;
}

Model *ResourceManager::LoadModel(const std::string &path) {
    auto it = models.find(path);
    if (it != models.end())
        return it->second;

    Model* m = new Model(path.c_str());
    models[path] = m;
    return m;
}

void ResourceManager::Clear() {
    for (auto& [_, v] : textures) delete v;
    for (auto& [_, v] : shaders)  delete v;
    for (auto& [_, v] : models)   delete v;
}

Texture *ResourceManager::TryLoadTexture(const std::string& path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    Texture* tex = new Texture(path.c_str(), texType, slot, format, pixelType);

    if (!tex || tex->ID == 0)
        return fallbackTexture;

    return tex;
}