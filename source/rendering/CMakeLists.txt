set(SOURCES
        SpriteRenderer.cpp SpriteRenderer.h)

add_library(Rendering ${SOURCES})

target_include_directories(Rendering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)