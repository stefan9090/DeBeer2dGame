set(SOURCES
        InputManager.cpp InputManager.h)

add_library(InputSystem ${SOURCES})

target_link_libraries(InputSystem glfw)
target_include_directories(InputSystem PUBLIC .)