add_subdirectory(spdlog)
add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(entt)
add_subdirectory(glm)
add_subdirectory(stb_image)


# Imgui target
set(IMGUI_DIR imgui)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends/)