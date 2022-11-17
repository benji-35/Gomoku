#
# Build your AI on WINDOWS !
#
#

cmake_minimum_required(VERSION 3.16)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)
	message(FATAL_ERROR
	"You can not use CMake to build from the root of it's source tree!\n"
	"Remove the CMakeCache.txt file from this directory, then create a separate directory\n"
	"(either below this directory or elsewhere), and then re-run CMake from there.")
endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)

# set exe name
set(EXE_NAME "MyAI_Gomoku" CACHE STRING "Game Name")

project(${EXE_NAME} LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(src/)

add_executable(${EXE_NAME} ${SOURCES} ${HEADERS})
