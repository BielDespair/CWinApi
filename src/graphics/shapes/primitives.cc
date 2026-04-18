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
    
    Mesh mesh;
    
    mesh.vertices = {
        Vertex { baseCenter + right * s + forward * s, color },
        Vertex { baseCenter + right * s - forward * s, color }, 
        Vertex { baseCenter - right * s - forward * s, color },
        Vertex { baseCenter - right * s + forward * s, color },
        Vertex { top, color}
    };

    mesh.indices = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    return mesh;
}