#include "Mesh.hh"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    VAO.Bind();

    VBO VBO(vertices);
	EBO EBO(indices);

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera) {
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}



void Mesh::Debug()
{
    std::cout << "Mesh Debug\n";
    std::cout << "Vertices: " << vertices.size() << "\n";
    std::cout << "Indices: " << indices.size() << "\n\n";

    for (size_t i = 0; i < vertices.size(); i++)
    {
        const Vertex& v = vertices[i];

        std::cout << "Vertex " << i << ":\n";
        std::cout << "  Pos:    " << v.pos.x << ", " << v.pos.y << ", " << v.pos.z << "\n";
        std::cout << "  Color:  " << v.color.x << ", " << v.color.y << ", " << v.color.z << "\n";
        std::cout << "  Normal: " << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << "\n";
        std::cout << "  UV:     " << v.texUV.x << ", " << v.texUV.y << "\n";
        std::cout << "\n";
    }

    std::cout << "Indices:\n";
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        std::cout << "  Tri " << (i / 3) << ": ";

        std::cout << indices[i] << ", ";
        if (i + 1 < indices.size()) std::cout << indices[i + 1] << ", ";
        if (i + 2 < indices.size()) std::cout << indices[i + 2];

        std::cout << "\n";
    }
}