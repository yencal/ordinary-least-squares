cmake_minimum_required(VERSION 3.8)

set(Project_Name estOLS)

project(${Project_Name} C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)