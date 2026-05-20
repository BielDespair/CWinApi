#include "Camera.hh"






Camera::Camera(Input& input) : input(input) {

}

void Camera::Resize(int width, int height) {
    this->width = width;
    this->height = height;
    if (height <= 0)
        height = 1;
    this->aspectRatio = (float)width / (float)height;


}
void Camera::Reset() {
    position = Vec3 {-1.5, 1.0, -1.5};
    forward = Vec3 { 0, 0, 0 }.normalize();
}
void Camera::Update(float dt) {

    Vec3 aux = (fabs(forward.y < 0.99f)) ? Vec3  {0, 1, 0 } : Vec3{ 1, 0, 0 };

    Vec3 right = forward.cross(aux);
    Vec3 up = right.cross(forward);

    forward = forward.normalize();

    if(input.IsActionDown(Action::CameraMoveForward)) {
        
        position = position + forward * SPEED * dt;
    }

    else if (input.IsActionDown(Action::CameraMoveBackwards)) {
        position = position - forward * SPEED * dt;
    }

    if(input.IsActionDown(Action::CameraMoveLeft)) {
        
        position = position - right * SPEED * dt;
    }

    else if (input.IsActionDown(Action::CameraMoveRight)) {
        position = position + right * SPEED * dt;
    }

    if (input.IsActionDown(Action::LookUp)) {
        pitch -= SPEED * dt;
    }
    else if (input.IsActionDown(Action::LookDown)) {
        pitch += SPEED * dt;
    }

    if (input.IsActionDown(Action::LookLeft)) {
        yaw += SPEED * dt;
    }
    else if (input.IsActionDown(Action::LookRight)) {
        yaw -= SPEED * dt;
    }

    if (input.IsActionDown(Action::MoveCamera)) {
        pitch -= input.deltaY * SENSIBILITY;
        yaw += input.deltaX * SENSIBILITY;
    }


    if (input.IsActionPressed(Action::Debug)) {
        printf("Position: (%f, %f, %f)", position.x, position.y, position.z);
    }


    pitch = std::clamp(pitch, -PITCH_LIMIT, PITCH_LIMIT);
    forward.x = cosf(yaw) * cosf(pitch);
    forward.y = sinf(pitch);
    forward.z = sinf(yaw) * cosf(pitch);
    forward = forward.normalize();

    glm::vec3 pos(position.x, position.y, position.z);
    glm::vec3 fwd(forward.x, forward.y, forward.z);
    glm::vec3 upv(up.x, up.y, up.z);

    glm::mat4 proj = glm::perspective(FOV, aspectRatio, CNEAR, CFAR);

    glm::mat4 view = glm::lookAt(
        pos,
        pos + fwd,
        upv
    );
    matrix = proj * view;
    

}