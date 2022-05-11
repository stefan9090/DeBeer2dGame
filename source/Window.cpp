//
// Created by beerd on 1/14/2022.
//

#include "Window.h"

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
            pData->inputManager.updateKeyInput(key, scancode, action, mods);
        });

        glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow *pWindow, int button, int action, int mods) {
            auto *pData = (Data*) glfwGetWindowUserPointer(pWindow);
            pData->inputManager.updateMouseButtonInput(button, action, mods);
        });

        glfwSetScrollCallback(m_pWindow, [](GLFWwindow *pWindow, double xOffset, double yOffset) {
            auto *pData = (Data*) glfwGetWindowUserPointer(pWindow);
            pData->inputManager.updateScrollInput(xOffset, yOffset);
        });

        glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow *pWindow, double xPos, double yPos) {
            auto *pData = (Data*) glfwGetWindowUserPointer(pWindow);
            pData->inputManager.updateCursorPos(xPos, yPos);
        });
    }

    Window::~Window()
    {
        if (m_pWindow)
        {
            glfwDestroyWindow(m_pWindow);
        }
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
