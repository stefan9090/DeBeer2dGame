set(SOURCES
        ResourceManager.cpp ResourceManager.h Shader.cpp Shader.h Texture.cpp Texture.h)

add_library(ResourceManagement ${SOURCES})

target_link_libraries(ResourceManagement PRIVATE glm glad stb_image Logging)

target_include_directories(ResourceManagement PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)