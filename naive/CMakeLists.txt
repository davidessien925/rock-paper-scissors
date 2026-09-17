cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_COMPILER ${CXX})

set(CMAKE_C_COMPILER ${CC})

project(rock_paper_scissors)

add_executable(rock_paper_scissors main.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
