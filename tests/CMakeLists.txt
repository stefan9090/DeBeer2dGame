add_subdirectory(gtest)

add_executable(tests EventSystem_test.cpp)

include_directories(${gtest_SOURCE_DIR}/include)
target_include_directories(tests PRIVATE ${gtest_SOURCE_DIR}/include)
target_link_libraries(tests gtest_main EventSystem)

include(GoogleTest)
gtest_discover_tests(tests)