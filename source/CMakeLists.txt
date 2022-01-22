add_subdirectory(events)
add_subdirectory(input)

set(SOURCES
        main.cpp
        Logger.cpp Logger.h Application.cpp Application.h Shader.cpp Shader.h input/InputManager.cpp input/InputManager.h Window.cpp Window.h)

add_executable(DeBeer2d ${SOURCES})

# Own libs
target_link_libraries(DeBeer2d EventSystem)
target_link_libraries(DeBeer2d InputSystem)

# External libs
target_link_libraries(DeBeer2d spdlog)
target_link_libraries(DeBeer2d glfw)
target_link_libraries(DeBeer2d glad)
target_link_libraries(DeBeer2d entt)
target_link_libraries(DeBeer2d imgui)
target_link_libraries(DeBeer2d glm)
target_link_libraries(DeBeer2d stb_image)