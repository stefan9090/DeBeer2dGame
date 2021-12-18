//
// Created by beerd on 12/17/2021.
//

#ifndef DEBEER2D_APPLICATION_H
#define DEBEER2D_APPLICATION_H

#include <glad/glad.h> // must be included before GLFW/glfw3.h
#include <GLFW/glfw3.h>

class Application
{
private:
    GLFWwindow* m_pWindow;

public:
    explicit Application() = default;
    ~Application();

    void init();
    void run();

private:
    static void glfwErrorCallback(int error, const char* description);
};


#endif //DEBEER2D_APPLICATION_H
