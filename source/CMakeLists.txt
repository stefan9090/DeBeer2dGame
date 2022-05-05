add_subdirectory(logging)
add_subdirectory(events)
add_subdirectory(input)
add_subdirectory(resource-management)
add_subdirectory(rendering)
add_subdirectory(scene)

set(SOURCES
        Application.cpp Application.h Window.cpp Window.h Layer.cpp Layer.h LayerStack.cpp LayerStack.h DeBeer2d.h CoreEvents.h)

add_library(DeBeer2d ${SOURCES})

target_include_directories(DeBeer2d PUBLIC .)

# Own libs
target_link_libraries(DeBeer2d EventSystem)
target_link_libraries(DeBeer2d InputSystem)
target_link_libraries(DeBeer2d ResourceManagement)
target_link_libraries(DeBeer2d Rendering)
target_link_libraries(DeBeer2d Scene)

# External libs
target_link_libraries(DeBeer2d spdlog)
target_link_libraries(DeBeer2d glfw)
target_link_libraries(DeBeer2d glad)
target_link_libraries(DeBeer2d entt)
target_link_libraries(DeBeer2d imgui)
target_link_libraries(DeBeer2d glm)
target_link_libraries(DeBeer2d stb_image)