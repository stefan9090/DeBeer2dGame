//
// Created by beerd on 1/14/2022.
//

#ifndef DEBEER2D_WINDOW_H
#define DEBEER2D_WINDOW_H

#include <glad/glad.h> // must be included before GLFW/glfw3.h
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <InputManager.h>
#include <Event.h>

#include <string>

class Window
{
private:
    GLFWwindow *m_pWindow = nullptr;
    InputManager m_input;

public:
    Window() = default;
    Window(const Window &rOther) = delete;
    Window(int screenWidth, int screenHeight, const std::string &strName, GLFWmonitor *pMonitor, EventBus &rEventBus);
    virtual ~Window();

    Window &operator=(const Window &rOther) = delete;
    Window &operator=(Window &&rOther) noexcept;

    GLFWwindow *getWindow() const;
    InputManager &getInput();

    void shouldClose(bool shouldClose);
    bool shouldClose();
    void makeContextCurrent();
    glm::vec<2, int> getFrameBufferSize();
    void swapBuffers();
};


#endif//DEBEER2D_WINDOW_H
