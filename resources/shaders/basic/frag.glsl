#version 330 core

in vec3 color;
out vec4 FragColor;


void main() {
    // gl_PrimitiveID é gerado automaticamente pelo OpenGL.
    // O primeiro triângulo é 0, o segundo é 1, e assim por diante.
    
    // O "% 6" garante que se você tiver mais de 6 triângulos, as cores se repetem sem dar erro.
    //int indiceCor = gl_PrimitiveID % 6;
    
    
    FragColor = vec4(color, 1.0);
}