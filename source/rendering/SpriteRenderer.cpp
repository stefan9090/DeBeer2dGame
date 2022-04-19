//
// Created by stefan on 4/8/22.
//

#include "SpriteRenderer.h"

#include "glm/ext.hpp"
#include <glad/glad.h>// must be included before GLFW/glfw3.h
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Components.h>
#include <Logger.h>

#include <entt.hpp>

void SpriteRenderer::init(const ResourceManager &rResources, int screenWidth, int screenHeight)
{
    m_pShader = rResources.getShader("sprite");
    if (m_pShader)
    {
        m_projection = glm::ortho(0.f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.f, -1.f, 1.f);

        m_pShader->setMat4("projection", m_projection);
    }
    else
    {
        LOG_ERROR("No sprite shader");
    }

    initRenderData();
}

void SpriteRenderer::drawScene(const Scene &rScene)
{
    rScene.getNative().view<Position, Renderable>().each([&](const Position &rPos, const Renderable &rRen) {
        this->drawSprite(rRen.pTexture, rPos.pos, rPos.size, 0.f, {});
    });
}

void SpriteRenderer::drawSprite(const std::shared_ptr<Texture> &pTexture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // prepare transformations
    if (!m_pShader) return;

    // prepare transformations
    m_pShader->use();

    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, glm::vec3(position, 0.0f));

    m_model = glm::translate(m_model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    m_model = glm::rotate(m_model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::translate(m_model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    m_model = glm::scale(m_model, glm::vec3(size, 1.0f));

    m_pShader->setMat4("model", m_model);
    m_pShader->setMat4("projection", m_projection);

    m_pShader->setVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    pTexture->use();

    glBindVertexArray(m_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
