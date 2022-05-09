set(SOURCES
        InputManager.cpp InputManager.h)

add_library(InputSystem ${SOURCES})

target_link_libraries(InputSystem glfw EventSystem Logging)
target_include_directories(InputSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)