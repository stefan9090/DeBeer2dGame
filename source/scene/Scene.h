//
// Created by stefan on 4/15/22.
//

#ifndef DEBEER2D_SCENE_H
#define DEBEER2D_SCENE_H

#include <functional>
#include <entt.hpp>
#include <glm/glm.hpp>

#include <Texture.h>

class Scene
{
private:
    entt::registry m_registry;

public:
    void addSprite(std::shared_ptr<Texture> rTexture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);

    const entt::registry &getNative() const;
};


#endif//DEBEER2D_SCENE_H
