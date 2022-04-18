//
// Created by stefan on 4/13/22.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

bool Texture::load(std::string_view strPath)
{
    bool success = false;

    int width;
    int height;
    int nrChannels;
    unsigned char *pData = stbi_load(strPath.data(), &width, &height, &nrChannels, 0);
    if (pData)
    {
        glGenTextures(1, &m_texture);

        this->use();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
        glGenerateMipmap(GL_TEXTURE_2D);

        success = true;
    }

    // Free data even if we failed to load it
    stbi_image_free(pData);


    return success;
}

void Texture::use() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
