set(SOURCES
        main.cpp
        Logger.cpp Logger.h Application.cpp Application.h)

add_executable(DeBeer2d ${SOURCES})

target_link_libraries(DeBeer2d spdlog)
target_link_libraries(DeBeer2d glfw)
target_link_libraries(DeBeer2d glad)
target_link_libraries(DeBeer2d entt)
target_link_libraries(DeBeer2d imgui)