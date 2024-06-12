cmake_minimum_required(VERSION 3.29)
project(matrix_lib)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/a7f443b80b105f940225332ed3c31f2790092f47.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(matrix_lib
        matrix_lib/Matrix.cpp
        matrix_lib/gaussian_elimination/operations.cpp
        matrix_lib/gaussian_elimination/elimination.cpp
        matrix_lib/gaussian_based.cpp
        matrix_lib/exceptions.cpp
)

add_executable(console_application console_application.cpp)
target_link_libraries(console_application matrix_lib)

enable_testing()

add_executable(tests
        tests/test_sum.cpp
        tests/test_sub.cpp
        tests/test_mul_scal.cpp
        tests/test_div.cpp
        tests/test_mul.cpp
        tests/test_minus.cpp
        tests/test_transpose.cpp
)
target_link_libraries(tests GTest::gtest_main matrix_lib)
include(GoogleTest)
gtest_discover_tests(tests)
