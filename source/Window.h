//
// Created by beerd on 1/14/2022.
//

#ifndef DEBEER2D_WINDOW_H
#define DEBEER2D_WINDOW_H

#include <glad/glad.h>// must be included before GLFW/glfw3.h
#include <glm/glm.hpp>

#include <Event.h>
#include <EventManager.h>
#include <InputManager.h>
#include <SpriteRenderer.h>

#include <string>

namespace Beer::internal
{
    class Window
    {
    private:
        GLFWwindow *m_pWindow = nullptr;

        struct Data {
            EventManager &rEventManager;
            InputManager inputManager;

            explicit Data(EventManager &eventManager)
                : rEventManager(eventManager)
                , inputManager(rEventManager)
            {}
        } m_data;

    public:
        Window(const Window &rOther) = delete;
        Window(int screenWidth, int screenHeight, const std::string &strName, GLFWmonitor *pMonitor, EventManager &rEventManager);
        virtual ~Window();

        Window &operator=(const Window &rOther) = delete;

        void makeContextCurrent();
        glm::vec<2, int> getFrameBufferSize();
        void swapBuffers();
    };
}// namespace Beer::internal

#endif//DEBEER2D_WINDOW_H
