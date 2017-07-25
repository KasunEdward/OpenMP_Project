cmake_minimum_required(VERSION 3.6)
project(OpenMP_Project)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Parallel.c Serial.c OptimizedVersion.c OV_Parallel.c)
add_executable(OpenMP_Project ${SOURCE_FILES})