//
// Created by beerd on 1/14/2022.
//

#include "Window.h"

Window::Window(int screenWidth, int screenHeight, const std::string &strName, GLFWmonitor *pMonitor)
    : m_pWindow(glfwCreateWindow(screenWidth, screenHeight, strName.c_str(), pMonitor, nullptr))
    , m_input(m_pWindow)
{
}

Window::~Window()
{
    if (m_pWindow)
    {
        glfwDestroyWindow(m_pWindow);
    }
}

Window &Window::operator=(Window &&rOther) noexcept
{
    this->m_pWindow = rOther.m_pWindow;
    this->m_input = std::move(rOther.m_input);

    rOther.m_pWindow = nullptr;

    return *this;
}

GLFWwindow *Window::getWindow() const
{
    return m_pWindow;
}

InputManager &Window::getInput()
{
    return m_input;
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
