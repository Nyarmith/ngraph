cmake_minimum_required(VERSION 2.8)
project(ngraph)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

#include_directories(util)
include_directories(include)
add_subdirectory(src)

#include_directories(util)
#include_directories(include)
#add_library(ngl STATIC )
#add_executable(exename main.cpp)
