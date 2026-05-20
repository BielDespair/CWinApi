#include "transform.hh"
#include <glm/ext/matrix_transform.hpp>


float normalize_rads(float r) {
    r = fmodf(r, TWO_PI);
    if (r < 0.0f)
        r += TWO_PI;
    return r;
}

glm::mat4 Transform::toMatrix() {
    const glm::mat4 identity = glm::mat4(1.0f);

    glm::mat4 T;
    glm::mat4 R;
    glm::mat4 S;

    T = glm::translate(identity, {position.x, position.y, position.z});

    R = identity;
    R = glm::rotate(R, rotation.x, glm::vec3(1, 0, 0));
    R = glm::rotate(R, rotation.y, glm::vec3(0, 1, 0));
    R = glm::rotate(R, rotation.z, glm::vec3(0, 0, 1));

    S = glm::scale(identity, {scale.x, scale.y, scale.z});
    
    return T * R * S;
}

void Transform::AddRotation(Vec3 delta) {
    rotation += delta;
    NormalizeRotation();
}

void Transform::ScaleBy(Vec3 factor) {
    scale += factor;
}

void Transform::SetPosition(Vec3 p) {
    position = p;
}
void Transform::SetRotation(Vec3 r) {
    rotation = r;
    NormalizeRotation();
}

void Transform::NormalizeRotation() {
    rotation.x = normalize_rads(rotation.x);
    rotation.y = normalize_rads(rotation.y);
    rotation.z = normalize_rads(rotation.z);
}

void Transform::Reset()
{
    const Vec3 identity = Vec3(1.0f);

    position = rotation = scale = identity;
}