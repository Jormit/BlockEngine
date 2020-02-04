#include "texture.hpp"
using namespace std;

Texture::Texture(const char* file) {
    texture.type = GL_TEXTURE_2D;
    glGenTextures(1, &(texture.id));
    glBindTexture(texture.type, texture.id);
    // Set wrapping parameters.
    glTexParameteri(texture.type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texture.type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set filtering parameters.
    glTexParameteri(texture.type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texture.type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load texture image.
    int tex_width, tex_height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file, &tex_width, &tex_height, &nrChannels, 0);

    // If texture loaded successfuly then generate mipmaps.
    if (data) {
        glTexImage2D(texture.type, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(texture.type);
    }
    else {
        cerr << "Could not load texture!" << endl;
        exit(1);
    }
    stbi_image_free(data);
}

void Texture::bindTexture(){
    glBindTexture(texture.type, texture.id);
}

unsigned int Texture::getId(){
    return texture.id;
}
