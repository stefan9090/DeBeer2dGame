//
// Created by beerd on 12/17/2021.
//

#include "Application.h"
#include "Logger.h"
#include "entt.hpp"
#include "Shader.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <chrono>

using namespace std::chrono;

const char *szGlslVersion = "#version 150";

Application::Application()
{
}

Application::~Application()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    LOG_INFO("exiting");
}

void Application::init()
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
    m_window = Window(screenWidth, screenHeight, "DeBeer2d", nullptr);

    if (!m_window.getWindow())
    {
        throw std::runtime_error("Failed to creat glfw window");
    }

    m_window.makeContextCurrent();

    glfwSwapInterval(1);// Enable vsync

    // Init imgui
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window.getWindow(), true);
    ImGui_ImplOpenGL3_Init(szGlslVersion);

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to init Glad");
    }

    Shader spriteShader{};
    if (!spriteShader.load("sprite.vert", "sprite.frag"))
    {
        LOG_ERROR("Failed to load sprite shader");
    }

    m_window.getInput().mapActionToKey(EInputAction::close, EInputKey::escape);
}

void Application::run()
{
    ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);

    while (!m_window.shouldClose())
    {
        glfwPollEvents();

        m_window.getInput().tick();

        ActionState closeAction = m_window.getInput().getActionState(EInputAction::close);

        if (closeAction.isActive && (closeAction.stateDuration > seconds(1)))
        {
            m_window.shouldClose(true);
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {// Show stats window
            ImGui::SetNextWindowSize(ImVec2{100, 50}, true);
            ImGui::Begin("stats:");

            ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        auto displaySize = m_window.getFrameBufferSize();
        glViewport(0, 0, displaySize.x, displaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window.swapBuffers();
    }
}

void Application::glfwErrorCallback(int error, const char *description)
{
    LOG_ERROR("Glfw Error {}: {}", error, description);
}
