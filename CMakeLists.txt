cmake_minimum_required(VERSION 3.16.3)
project(DeBeer2d)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(RESOURCES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
add_compile_definitions(SHADERS_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/resources/shaders/")
add_compile_definitions(TEXTURES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/resources/textures/")

add_subdirectory(external)
add_subdirectory(source)

#include(CTest) # note: this adds a BUILD_TESTING which defaults to ON
#if(BUILD_TESTING)
#    add_subdirectory(tests)
#endif()
