set(SOURCES
        Event.cpp EventClass.h FamilyType.h EventManager.cpp EventManager.h CoreEvents.h)

add_library(EventSystem ${SOURCES})

target_link_libraries(EventSystem entt glm)
target_include_directories(EventSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)