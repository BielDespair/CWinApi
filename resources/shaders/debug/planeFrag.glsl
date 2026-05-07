#version 330 core

in vec3 WorldPos;

layout (location = 0) out vec4 FragColor;

uniform float gGridCellSize = 0.05;

uniform vec4 gGridColorThin  = vec4(0.5, 0.5, 0.5, 1.0);
uniform vec4 gGridColorThick = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    // Coordenada da grid
    vec2 coord = WorldPos.xz / gGridCellSize;

    // Distância até a linha mais próxima
    vec2 grid = abs(fract(coord - 0.5) - 0.5);

    // Anti-aliasing baseado em derivadas de tela
    vec2 fw = fwidth(coord);

    // Evita divisão por zero
    fw = max(fw, vec2(1e-6));

    // Distância em pixels
    vec2 lineDist = grid / fw;

    // Linha aparece quando X ou Z está perto da borda
    float line = min(lineDist.x, lineDist.y);

    // Alpha final
    float alpha = 1.0 - clamp(line, 0.0, 1.0);

    vec4 color = gGridColorThin;
    color.a *= alpha;

    FragColor = color;
}