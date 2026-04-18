#version 330 core


uniform mat4 gVP;
//uniform mat4 projection;

const vec3 Pos[4] = vec3[4](
    vec3(-1.0, 0.0, -1.0),
    vec3(-1.0, 0.0, 1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(1.0, 0.0, -1.0)
);


const int Indices[6] = int[6](0, 1, 2, 0, 2, 3);


void main() {

    int Index = Indices[gl_VertexID];
    vec4 vPos = vec4(Pos[Index], 1.0);
    gl_Position = gVP * vPos;

}