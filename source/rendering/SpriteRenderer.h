//
// Created by stefan on 4/8/22.
//

#ifndef DEBEER2D_SPRITERENDERER_H
#define DEBEER2D_SPRITERENDERER_H

#include <ResourceManager.h>
#include <Shader.h>
#include <Texture.h>
#include <Scene.h>

#include <memory>
#include <glm/glm.hpp>

class SpriteRenderer
{
private:
    std::shared_ptr<Shader> m_pShader;
    unsigned int m_quadVAO;

    glm::mat4 m_model;
    glm::mat4 m_projection;
public:
    void init(const ResourceManager &rResources, int screenWidth, int screenHeight);
    void drawSprite(const std::shared_ptr<Texture> &pTexture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    void drawScene(const Scene &rScene);

private:
    void initRenderData();
};


#endif//DEBEER2D_SPRITERENDERER_H
