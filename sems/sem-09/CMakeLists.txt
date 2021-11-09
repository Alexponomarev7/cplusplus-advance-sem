project(test_foo)
cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_library(lib lib.cpp)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC lib)

include_directories("/usr/local/include/")
add_executable(main_test tests.cpp)
gtest_add_tests(TARGET main_test)
target_link_libraries(main_test PUBLIC lib GTest::gtest GTest::gtest_main)
