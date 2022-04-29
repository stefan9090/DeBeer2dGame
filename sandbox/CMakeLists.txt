cmake_minimum_required(VERSION 3.16.3)
project(sandbox)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        main.cpp)

add_executable(sandbox ${SOURCES})

target_link_libraries(sandbox PRIVATE DeBeer2d)