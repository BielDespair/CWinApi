#include "primitives.hh"




Mesh buildPyramid(float b, float h, Vec3 c, Vec3 d, Vec3 color) {


    Vec3 dir = d.normalize();
    Vec3 top = c + dir * (h * 0.5f);
    Vec3 baseCenter = c - dir * (h * 0.5f);
    
    // Só pra n colidir com paralelo ao y. Se for mt próximo, pega o vetor canônico X
    Vec3 aux = fabs(d.y) < 0.99f ? Vec3{0, 1, 0} : Vec3{1, 0, 0};
    
    Vec3 forward = dir.cross(aux);
    Vec3 right = forward.cross(dir);
    
    float s = b * 0.5f;
    
    std::vector<Vertex> vertices = {
        Vertex { baseCenter + right * s + forward * s, color },
        Vertex { baseCenter + right * s - forward * s, color }, 
        Vertex { baseCenter - right * s - forward * s, color },
        Vertex { baseCenter - right * s + forward * s, color },
        Vertex { top, color}
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };
    
    return Mesh(vertices, indices);
}

Mesh buildCylinder(float r, float h, int segments, Vec3 c, Vec3 d, Vec3 color) {
    const float PI = 3.14159265358979323846f;
    Vec3 dir = d.normalize();
    Vec3 topCenter  = c + dir * (h * 0.5f);
    Vec3 baseCenter = c - dir * (h * 0.5f);

    Vec3 aux = fabs(dir.y) < 0.99f ? Vec3{0,1,0} : Vec3{1,0,0};

    Vec3 forward = dir.cross(aux).normalize();
    Vec3 right   = forward.cross(dir).normalize();

    
    // centros
    uint32_t baseCenterIdx = 0;
    uint32_t topCenterIdx  = 1;
    
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    
    vertices.push_back({ baseCenter, color });
    vertices.push_back({ topCenter,  color });

    // anéis
    for (int i = 0; i < segments; ++i) {
        float a = (2.0f * PI * i) / segments;
        float ca = cos(a);
        float sa = sin(a);

        Vec3 offset = right * ca * r + forward * sa * r;

        vertices.push_back({ baseCenter + offset, color }); // base
        vertices.push_back({ topCenter  + offset, color }); // topo
    }

    // índices
    for (int i = 0; i < segments; ++i) {
        int next = (i + 1) % segments;

        uint32_t b0 = 2 + i*2;
        uint32_t t0 = b0 + 1;
        uint32_t b1 = 2 + next*2;
        uint32_t t1 = b1 + 1;

        // base
        indices.insert(indices.end(), {
            baseCenterIdx, b1, b0
        });

        indices.insert(indices.end(), {
            topCenterIdx, t0, t1
        });

        // lateral (quad -> 2 tri)
        indices.insert(indices.end(), {
            b0, b1, t1,
            b0, t1, t0
        });
    }

    return Mesh(vertices, indices);
}

Mesh buildPlane(float w, float h, Vec3 c, Vec3 orientation)
{
    Vec3 dir = orientation.normalize();

    Vec3 aux = fabs(dir.y) < 0.99f ? Vec3{0, 1, 0} : Vec3{1, 0, 0};

    Vec3 right = dir.cross(aux).normalize();
    Vec3 forward = right.cross(dir).normalize();

    float hw = w * 0.5f;
    float hh = h * 0.5f;

    std::vector<Vertex> vertices = {
        { c - right * hw - forward * hh, {1.0f, 1.0f, 1.0f}, dir, {0.0f, 0.0f} },
        { c + right * hw - forward * hh, {1.0f, 1.0f, 1.0f}, dir, {1.0f, 0.0f} },
        { c + right * hw + forward * hh, {1.0f, 1.0f, 1.0f}, dir, {1.0f, 1.0f} },
        { c - right * hw + forward * hh, {1.0f, 1.0f, 1.0f}, dir, {0.0f, 1.0f} }
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        0, 2, 3
    };

    return Mesh(vertices, indices);
}

Mesh buildCube(float size, Vec3 c)
{
    
    return Mesh({}, {});
}
