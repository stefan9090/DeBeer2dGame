set(SOURCES
        Logger.cpp Logger.h)

add_library(Logging ${SOURCES})

target_compile_definitions(Logging PUBLIC SPDLOG_ACTIVE_LEVEL=0)

target_link_libraries(Logging PUBLIC spdlog)

target_include_directories(Logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)