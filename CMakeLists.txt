cmake_minimum_required(VERSION 3.29)
project(matrix_lib)

set(CMAKE_CXX_STANDARD 20)

add_library(matrix_lib
        matrix_lib/Matrix.cpp
        matrix_lib/gaussian_elimination/operations.cpp
        matrix_lib/gaussian_elimination/elimination.cpp
)
