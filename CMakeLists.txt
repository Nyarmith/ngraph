cmake_minimum_required(VERSION 2.8)
project(ngraph)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_BUILD_TYPE Debug)

#warnings at max
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W4")
endif ( MSVC )

#include_directories(util)
include_directories(include)
#add_subdirectory(src)
add_subdirectory(tests)

#include_directories(util)
#include_directories(include)
#add_library(ngl STATIC )
#add_executable(exename main.cpp)
