//
// Created by beerd on 12/17/2021.
//

#include "Application.h"
#include <entt.hpp>

#include <Logger.h>
#include <Texture.h>

using namespace std::chrono;

namespace Beer
{
    Application::Application()
    {
        // Init glfw
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to init GLFW");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwSetErrorCallback(glfwErrorCallback);

        int screenWidth = 800;
        int screenHeight = 600;
        m_pWindow = std::make_unique<internal::Window>(screenWidth, screenHeight, "DeBeer2d", nullptr, m_eventManager);

        if (!m_pWindow->getWindow())
        {
            throw std::runtime_error("Failed to creat glfw window");
        }

        m_pWindow->makeContextCurrent();

        glfwSwapInterval(1);// Enable vsync

        // Init glad
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to init Glad");
        }

        m_resources.loadShader("sprite");
        m_renderer.init(m_resources, screenWidth, screenHeight);

        m_pWindow->getInput().mapActionToKey(EInputAction::close, EInputKey::escape);

//        m_eventBus.subscribeTo<WindowResizeEvent>(*this);
        m_eventBus.subscribeTo<WindowCloseEvent>(*this);

        m_eventManager.pushBack(&m_eventBus);
    }

    Application::~Application()
    {

        LOG_INFO("exiting");
    }

    void Application::run()
    {
        glm::vec4 clear_color = glm::vec4(0.f, 0.f, 0.f, 1.00f);

        while (m_doRun)
        {
            glfwPollEvents();

            auto displaySize = m_pWindow->getFrameBufferSize();
            glViewport(0, 0, displaySize.x, displaySize.y);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            m_renderer.drawScene(m_scene);

            m_pWindow->swapBuffers();
        }
    }

    void Application::glfwErrorCallback(int error, const char *description)
    {
        LOG_ERROR("Glfw Error {}: {}", error, description);
    }


    void Application::loadTexture(std::string_view szPath)
    {
        m_resources.loadTexture(szPath);
    }

    void Application::initTextures()
    {
        m_resources.initTextures();
    }

    bool Application::receive(const WindowResizeEvent &rEvent)
    {
        return true;
    }

    bool Application::receive(const WindowCloseEvent &rEvent)
    {
        m_doRun = false;
        return true;
    }
}// namespace DeBeer2d
