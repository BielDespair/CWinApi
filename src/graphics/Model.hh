#pragma once

#include "graphics/Mesh.hh"
#include "scene/Camera.hh"

#include "render/Shader.hh"

struct ObjIndex {
    int v = -1;
    int vt = -1;
    int vn = -1;

    bool operator==(const ObjIndex& o) const {
        return v == o.v && vt == o.vt && vn == o.vn;
    }
};

struct ObjIndexHash {
    size_t operator()(const ObjIndex& k) const {
        size_t h1 = std::hash<int>()(k.v);
        size_t h2 = std::hash<int>()(k.vt);
        size_t h3 = std::hash<int>()(k.vn);

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};


class Model {
    public:

        Model(Mesh& mesh);
        Model(std::vector<Mesh> meshes);
        Model(const char* filePath);
        void Draw(Shader& shader, Camera& camera);

    private:
        std::vector<Mesh> meshes;
};