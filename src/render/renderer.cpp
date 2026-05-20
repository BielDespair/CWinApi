#include "Renderer.hh"



void Renderer::Submit(Mesh* mesh, Texture* texture) {
    batches[texture].push_back(mesh);
}


void Renderer::Flush(Shader& shader, Camera& camera) {
    for (auto& [texture, meshes] : batches) {

        texture->Bind(); // shader + textures

        for (auto* mesh : meshes) {
            mesh->Draw(shader, camera);
        }
    }
}