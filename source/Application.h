//
// Created by beerd on 12/17/2021.
//

#ifndef DEBEER2D_APPLICATION_H
#define DEBEER2D_APPLICATION_H

//#include <glad/glad.h> // must be included before GLFW/glfw3.h
//#include <GLFW/glfw3.h>

#include "Window.h"
#include <ResourceManager.h>
#include <SpriteRenderer.h>

namespace DeBeer2d
{
    class Application
    {
    private:
        EventBus m_eventBus;
        Window m_window;
        ResourceManager m_resources;
        SpriteRenderer m_renderer;
        Scene m_scene;

    protected:
        void loadTexture(std::string_view szPath);
        void initTextures();

        bool shouldClose();

    public:
        explicit Application();
        ~Application();

        void updateApp();

    private:
        static void glfwErrorCallback(int error, const char *description);
    };
}

#endif//DEBEER2D_APPLICATION_H
