
#pragma once

#include <algorithm>


#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


#include "math/Vector.hh"
#include "input/input.hh"






class Camera {
    public:
        glm::mat4 matrix = glm::mat4(1.0f);
        
        Vec3 position = Vec3 {-1.5, 1.0, -1.5};
        Vec3 forward = Vec3 { 1.0, 0.0, -1.0 }.normalize();

        bool lockCenter = true;
    
    
    
        void Resize(int width, int height);
        void Reset();
        void Update(float dt);
        
        Camera(Input& input);
        
        
        private:
        
        const Vec3 WORLD_UP = Vec3 { 0.0f, 1.0f, 0.0f };
        const float CNEAR = 0.05f; 
        const float CFAR = 100.0f;
        const float SPEED = 0.5f;
        const float SENSIBILITY = 0.05f;
        const float FOV = glm::pi<float>()/3; // 60°
        const float PITCH_LIMIT = glm::radians(89.0f);

        int width, height;
        float aspectRatio;

        glm::mat4 projection = glm::mat4(1.0f);
        
        
        
        float sensitivity = 100.0f;
        float yaw, pitch;

        
        

        Input& input;
};