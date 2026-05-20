#version 330 core

in vec3 color;
in vec2 texCoord;
out vec4 FragColor;


uniform bool useTexture;
uniform sampler2D tex0;


void main() {
    // gl_PrimitiveID é gerado automaticamente pelo OpenGL.
    // O primeiro triângulo é 0, o segundo é 1, e assim por diante.
    
    // O "% 6" garante que se você tiver mais de 6 triângulos, as cores se repetem sem dar erro.
    //int indiceCor = gl_PrimitiveID % 6;
    
    
    if (useTexture)
        FragColor = texture(tex0, texCoord);
    else
        FragColor = vec4(color, 1.0);
}