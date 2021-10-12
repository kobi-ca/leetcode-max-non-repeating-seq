cmake_minimum_required(VERSION 3.21)
project(leetcode_max_non_repeating_seq)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
add_executable(leetcode_max_non_repeating_seq main.cpp)
target_link_libraries(leetcode_max_non_repeating_seq PRIVATE CONAN_PKG::fmt CONAN_PKG::gtest)

add_test(leetcode_max_non_repeating_seq leetcode_max_non_repeating_seq)
