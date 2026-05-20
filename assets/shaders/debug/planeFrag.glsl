#version 330 core

in vec3 WorldPos;

layout (location = 0) out vec4 FragColor;

uniform float gGridCellSize = 0.2;

uniform float gFadeStart = 25.0;
uniform float gFadeEnd   = 100.0;

uniform vec4 gGridColorThin = vec4(0.5, 0.5, 0.5, 1.0) / 2;

void main()
{
    vec2 coord = WorldPos.xz / gGridCellSize;

    vec2 grid = abs(fract(coord - 0.5) - 0.5);
    grid /= fwidth(coord);

    float line = min(grid.x, grid.y);
    float alpha = 1.0 - clamp(line, 0.0, 1.0);

    // distância ao centro da grid
    float dist = length(WorldPos.xz);

    float fade = 1.0 - smoothstep(gFadeStart, gFadeEnd, dist);

    vec4 color = gGridColorThin;
    color.a *= alpha * fade;
    color.a = max(color.a, 0.2);

    FragColor = color;
}