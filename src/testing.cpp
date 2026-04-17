#include <cstdlib>
#include <graphics/triangulation.hh>

#include <iostream>

void printMesh(const Mesh2D& mesh)
{
    std::cout << "Vertices (" << mesh.vertexCount << "):\n";

    for (size_t i = 0; i < mesh.vertexCount; i++)
    {
        std::cout << i << ": ("
                  << mesh.vertices[i].x << ", "
                  << mesh.vertices[i].y << ")\n";
    }

    std::cout << "\nIndices (" << mesh.indices.size() << "):\n";

    for (size_t i = 0; i < mesh.indices.size(); i += 3)
    {
        std::cout << mesh.indices[i] << ", "
                  << mesh.indices[i + 1] << ", "
                  << mesh.indices[i + 2] << "\n";
    }
}

int main() {


    Vec2 vertices[] = {
        { 0.0f, 0.9f },

        { 0.35f, 1.0f },
        { 0.7f, 0.7f },
        { 0.6f, 0.2f },
        { 0.3f, -0.2f },
        { 0.0f, -0.8f },

        { -0.3f, -0.2f },
        { -0.6f, 0.2f },
        { -0.7f, 0.7f },
        { -0.35f, 1.0f }
    };


    Mesh2D result = triangulate2D(vertices, sizeof(vertices) / sizeof(vertices[0]));

    printMesh(result);

    return EXIT_SUCCESS;
}