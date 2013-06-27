cmake_minimum_required (VERSION 2.8)
project(Instantiation)

#=================== compiler & flags ===================
SET(CMAKE_CXX_COMPILER "g++-4.7")
SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -O3 -pedantic")

#=================== set paths ===================
set(SRC "${PROJECT_SOURCE_DIR}/.")
set(LIB impl)

#=================== include directories ===================
include_directories("${SRC}")

add_library(${LIB} 03_01_impl.cpp)
add_executable(03_01_use_tpl_like_classes 03_01_use_tpl_like_classes.cpp)
target_link_libraries(03_01_use_tpl_like_classes ${LIB})
