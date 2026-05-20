#include "Model.hh"


#include <string>
#include <vector>
#include <iostream>
#include <fstream>


Model::Model(Mesh& mesh) {
    meshes.push_back(mesh);
}

Model::Model(std::vector<Mesh> meshes) {
    this->meshes = std::move(meshes);
}

Model::Model(const char* filePath) {

    std::vector<Vertex> vertices;

    std::vector<Vec3> positions;
    std::vector<Vec3> normals;
    std::vector<Vec2> texcoords;
    std::vector<uint32_t> indices;
    std::unordered_map<ObjIndex, uint32_t, ObjIndexHash> cache;

    auto addVertex = [&](const ObjIndex& idx) -> uint32_t
    {
        auto it = cache.find(idx);
        if (it != cache.end())
            return it->second;

        Vertex vtx;

        // Adicione o "- 1" aqui!
        vtx.pos = positions[idx.v - 1];
        vtx.color = Vec3{ 1.0f, 1.0f, 1.0f };

        // E aqui também (se for maior que zero)
        vtx.texUV = (idx.vt > 0)
            ? texcoords[idx.vt - 1]
            : Vec2{0, 0};

        // E aqui!
        vtx.normal = (idx.vn > 0)
            ? normals[idx.vn - 1]
            : Vec3{0, 0, 0};

        uint32_t index = (uint32_t)vertices.size();
        vertices.push_back(vtx);
        cache[idx] = index;

        return index; // Lembre-se de retornar 'index' e não 'idx.v'
    };

    std::string line;
    std::ifstream file(filePath);

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        
        const char* p = line.c_str();

        if(p[0] == 'v' && p[1] == ' ') {
            char* end;

            Vec3 v;
            v.x = strtof(p + 2, &end);
            v.y = strtof(end, &end);
            v.z = strtof(end, &end);
            positions.push_back(v);
        }

        else if (p[0] == 'v' && p[1] == 'n' && p[2] == ' ') {
            char* end;
            Vec3 vn;

            vn.x = strtof(p + 3, &end);
            vn.y = strtof(end, &end);
            vn.z = strtof(end, &end);

            normals.push_back(vn);
        }

        else if (p[0] == 'v' && p[1] == 't' && p[2] == ' ') {
            char* end;
            Vec2 vt;

            vt.x = strtof(p + 3, &end);
            vt.y = strtof(end, &end);
            texcoords.push_back(vt);
        }

        else if (p[0] == 'f' && p[1] == ' ') {
            ObjIndex idx[3];
            char* end;
            p += 2;

            for (int i = 0; i < 3; i++) {
                // Inicializa com 0 (indicando que não existe)
                idx[i].v = 0; idx[i].vt = 0; idx[i].vn = 0;

                // Pula espaços em branco entre os vértices da face
                while (*p == ' ') p++;

                // Lê a Posição (obrigatória)
                idx[i].v = strtol(p, &end, 10);
                p = end;

                // Verifica se há mais atributos (UV ou Normal)
                if (*p == '/') {
                    p++; // Pula a primeira '/'
                    
                    // Se o próximo caractere NÃO for '/', significa que temos a UV
                    if (*p != '/') { 
                        idx[i].vt = strtol(p, &end, 10);
                        p = end;
                    }
                    
                    // Verifica se há a segunda barra para a Normal
                    if (*p == '/') {
                        p++; // Pula a segunda '/'
                        idx[i].vn = strtol(p, &end, 10);
                        p = end;
                    }
                }
            }
            
            indices.push_back(addVertex(idx[0]));
            indices.push_back(addVertex(idx[1]));
            indices.push_back(addVertex(idx[2]));
        }
    }

    Mesh mesh(vertices, indices);
    meshes.push_back(mesh);
}

void Model::Draw(Shader& shader, Camera &camera) {
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader, camera);
    }
}