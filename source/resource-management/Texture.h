//
// Created by stefan on 4/13/22.
//

#ifndef DEBEER2D_TEXTURE_H
#define DEBEER2D_TEXTURE_H

#include <string>

class Texture
{
private:
    unsigned int m_texture;

    unsigned char *pData;
    int m_width;
    int m_height;
    int m_nrChannels;
public:
    bool load(std::string_view strPath);
    bool init();
    void use() const;
};


#endif//DEBEER2D_TEXTURE_H
