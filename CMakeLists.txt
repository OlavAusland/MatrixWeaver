cmake_minimum_required(VERSION 3.8)

#set(CMAKE_CXX_COMPILER "g++")

project(MatrixWeaver VERSION 0.0.0 LANGUAGES C CXX)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

include_directories("${CMAKE_PROJECT_NAME}" "${CMAKE_SOURCE_DIR}/include")
add_executable(${CMAKE_PROJECT_NAME} main.cpp ${SOURCES})
