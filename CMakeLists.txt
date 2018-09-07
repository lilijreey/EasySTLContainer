cmake_minimum_required(VERSION 3.5)
project(easySTL)

set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "-Wall -std=c++14")

#add_library(easystl INTERFACE)
#target_sources(easystl INTERFACE src/estl.hpp)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(estl_test src/estl.hpp test/estl_test.cpp src/estl_select_iter.hpp)
target_link_libraries(estl_test gtest_main gtest pthread)



add_test(FooTest estl_test)

