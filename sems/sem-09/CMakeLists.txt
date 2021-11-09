project(test_foo)
cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED CONFIG)

add_library(lib lib.cpp)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC lib)

include_directories("/usr/local/include/")
add_executable(main_test tests.cpp)
target_link_libraries(main_test PUBLIC lib GTest::gtest GTest::gtest_main)
target_link_libraries(main_test PUBLIC GTest::gmock GTest::gmock_main)
include(GoogleTest)
gtest_discover_tests(main_test)
