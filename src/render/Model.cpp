#include "Model.h"


#include <string>
#include <vector>
#include <iostream>
#include <fstream>


Model::Model(Mesh& mesh) {
    meshes.push_back(mesh);
}

Model::Model(const char* filePath) {

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    std::string line;
    std::ifstream file(filePath);

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        
        const char* p = line.c_str();

        if(p[0] == 'v' && p[1] == ' ') {
            Vertex vertex;
            char* end;

            vertex.pos.x = strtof(p + 2, &end);
            vertex.pos.y = strtof(end, &end);
            vertex.pos.z = strtof(end, &end);
            vertex.color = Vec3 {1.0f, 1.0f, 1.0f};
            vertices.push_back(vertex);
        }

        else if (p[0] == 'f' && p[1] == ' ') {

            int v[3], vt[3], vn[3];
            char* end;
            p += 2;

            for (int i = 0; i < 3; i++) {
                
                v[i] = strtol(p, &end, 10);
                vt[i] = strtol(end + 1, &end, 10);
                vn[i] = strtol(end + 1, &end, 10);
                p = end + 1;

                indices.push_back(v[i] - 1);
            }
        }
    }

    Mesh mesh(vertices, indices);
    meshes.push_back(mesh);
}

void Model::Draw(Shader &shader, Camera &camera) {
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader, camera);
    }
}