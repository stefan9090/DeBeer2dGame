set(SOURCES
        Event.cpp)

add_library(EventSystem ${SOURCES})

target_link_libraries(EventSystem entt)
target_include_directories(EventSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)