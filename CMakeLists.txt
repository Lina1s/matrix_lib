cmake_minimum_required(VERSION 3.29)
project(matrix_lib)

set(CMAKE_CXX_STANDARD 20)

add_library(matrix_lib
        matrix_lib/Matrix.cpp
        matrix_lib/gaussian_elimination/operations.cpp
        matrix_lib/gaussian_elimination/elimination.cpp
        matrix_lib/gaussian_based.cpp
        matrix_lib/exceptions.cpp
)

add_executable(console_application console_application.cpp)
target_link_libraries(console_application matrix_lib)
