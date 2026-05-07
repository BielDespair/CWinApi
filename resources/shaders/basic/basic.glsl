#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 viewProj;

//uniform mat4 projection;


out vec3 color;

void main() {




    // x' = xcos(o) - ysin(o)
    // y' = xsin(o) + ycos(o)
    gl_Position = viewProj * model * vec4(aPos, 1.0f);
    //gl_Position = projection * view * model * vec4(aPos, 1.0);
    color = aColor;
}