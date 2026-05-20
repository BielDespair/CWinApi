#include "Texture.hh"



Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    type = texType;

    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    if (bytes == nullptr) {
        widthImg = heightImg = 1;
        numColCh = 0;
    }

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(texType, GL_TEXTURE_BORDER_COLOR, flatColor);

    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}



void Texture::Bind() {
    glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}


void Texture::Delete() {
    glDeleteTextures(1, &ID);
}