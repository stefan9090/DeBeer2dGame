set(SOURCES
        Scene.cpp Scene.h)

add_library(Scene ${SOURCES})

target_link_libraries(Scene PUBLIC entt Logging ResourceManagement glm)

target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)