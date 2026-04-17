#include <vector.hh>
#include <cstdint>


struct Vertex {
    Vec3 pos;
    Vec3 bary;
};



void assignBarycentric(Vertex vertices[], const uint32_t indices[], size_t indicesSize) {
    
    // size Tem que ser múltiplo de 3
    if (indicesSize % 3 != 0) {
        return;
    }

    // A cada 3, formamos um triangulo
    for (size_t i = 0; i < indicesSize; i+= 3)
    {
        uint32_t a = indices[i + 0];
        uint32_t b = indices[i + 1];
        uint32_t c = indices[i + 2];

        vertices[a].bary = Vec3{ 1.0f, 0.0f, 0.0f };
        vertices[b].bary = Vec3{ 0.0f, 1.0f, 0.0f };
        vertices[c].bary = Vec3{ 0.0f, 0.0f, 1.0f };
    }
    
}