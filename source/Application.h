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
#include <EventManager.h>
#include <Event.h>
#include "CoreEvents.h"

namespace Beer
{
    class Application : private internal::EventClass<Application>
    {
    private:
        internal::EventManager m_eventManager;
        internal::EventEndPoint m_eventBus;
        Window m_window;
        ResourceManager m_resources;
        SpriteRenderer m_renderer;
        Scene m_scene;

    protected:
        void loadTexture(std::string_view szPath);
        void initTextures();

    public:
        explicit Application();
        ~Application();

        void run();

        bool receive(const WindowResizeEvent &rEvent);

    private:
        static void glfwErrorCallback(int error, const char *description);
    };
}

#endif//DEBEER2D_APPLICATION_H
