#include <math/Vector.hh>
#include <vector>


struct Mesh2D {
    Vec2* vertices;
    size_t vertexCount;

    std::vector<int> indices;
};





Mesh2D triangulate2D(Vec2* vertices, size_t size);

int get_circular(const std::vector<int>& list, int i);
bool is_point_in_triangle(Vec2 p, Vec2 a, Vec2 b, Vec2 c);