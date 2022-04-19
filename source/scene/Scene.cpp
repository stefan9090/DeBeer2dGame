//
// Created by stefan on 4/15/22.
//

#include "Scene.h"

#include <Components.h>

void Scene::addSprite(std::shared_ptr<Texture> pTexture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    entt::entity newEnt = m_registry.create();

    m_registry.emplace<Position>(newEnt, position, size);
    m_registry.emplace<Renderable>(newEnt, pTexture);
}

const entt::registry &Scene::getNative() const
{
    return m_registry;
}
