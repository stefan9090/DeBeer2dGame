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
public:
    bool load(std::string_view strPath);
    void use() const;
};


#endif//DEBEER2D_TEXTURE_H
