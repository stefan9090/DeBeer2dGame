//
// Created by beerd on 1/14/2022.
//

#include "Window.h"

#include <glm/ext.hpp>

#include "CoreEvents.h"

namespace Beer::internal
{
    Window::Window(int screenWidth, int screenHeight, const std::string &strName, GLFWmonitor *pMonitor, EventManager &rEventManager)
        : m_pWindow(glfwCreateWindow(screenWidth, screenHeight, strName.c_str(), pMonitor, nullptr))
        , m_data(rEventManager)
    {

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow *pWindow) {
            auto *pData = (Data*) glfwGetWindowUserPointer(pWindow);
            WindowCloseEvent closeEvent;
            pData->rEventManager.publishEvent<WindowCloseEvent>(closeEvent);
        });

        glfwSetKeyCallback(m_pWindow, [](GLFWwindow *pWindow, int key, int scancode, int action, int mods) {
            auto *pData = (Data*) glfwGetWindowUserPointer(pWindow);
            pData->inputManager.update(key, scancode, action, mods);
        });
    }

    Window::~Window()
    {
        if (m_pWindow)
        {
            glfwDestroyWindow(m_pWindow);
        }
    }

    GLFWwindow *Window::getWindow() const
    {
        return m_pWindow;
    }

    void Window::shouldClose(bool shouldClose)
    {
        glfwSetWindowShouldClose(m_pWindow, shouldClose);
    }

    bool Window::shouldClose()
    {
        return (glfwWindowShouldClose(m_pWindow) != 0);
    }

    void Window::makeContextCurrent()
    {
        if (m_pWindow)
        {
            glfwMakeContextCurrent(m_pWindow);
        }
    }

    glm::vec<2, int> Window::getFrameBufferSize()
    {
        if (!m_pWindow) return {};

        glm::vec<2, int> dimensions{};
        glfwGetFramebufferSize(m_pWindow, &dimensions.x, &dimensions.y);
        return dimensions;
    }

    void Window::swapBuffers()
    {
        if (m_pWindow)
        {
            glfwSwapBuffers(m_pWindow);
        }
    }
}// namespace Beer::internal

//void Window::render(const SpriteRenderer &rRenderer)
//{
//
//}
