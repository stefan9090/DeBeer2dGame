//
// Created by stefan on 4/18/22.
//

#ifndef DEBEER2D_COMPONENTS_H
#define DEBEER2D_COMPONENTS_H

#include <glm/glm.hpp>

#include <Texture.h>

struct Position
{
    glm::vec2 pos;
    glm::vec2 size;
};

struct Renderable
{
    std::shared_ptr<Texture> pTexture;
};

#endif//DEBEER2D_COMPONENTS_H
