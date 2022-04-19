//
// Created by stefan on 4/13/22.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

bool Texture::load(std::string_view strPath)
{
    pData = stbi_load(strPath.data(), &m_width, &m_height, &m_nrChannels, 0);
    if (!pData)
    {
        stbi_image_free(pData);
    }

    return (pData != nullptr);
}

bool Texture::init()
{
    glGenTextures(1, &m_texture);

    if (m_texture != 0)
    {
        this->use();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free data even if we failed to load it
        stbi_image_free(pData);
    }

    return (m_texture != 0);
}

void Texture::use() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
