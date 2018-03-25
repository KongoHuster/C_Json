cmake_minimum_required(VERSION 3.9)
project(untitled C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS -static)
add_executable(untitled main.c cJSON.c cJSON.h)