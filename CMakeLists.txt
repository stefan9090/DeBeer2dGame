cmake_minimum_required(VERSION 3.19)
project(DeBeer2d)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(RESOURCES_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/resource/")
add_compile_definitions(SHADERS_LOCATION="${CMAKE_CURRENT_SOURCE_DIR}/resource/shaders/")

add_subdirectory(external)
add_subdirectory(source)