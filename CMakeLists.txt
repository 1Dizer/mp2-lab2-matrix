cmake_minimum_required(VERSION 3.14)
project(mp2_lab2_matrix CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Современный Google Test через FetchContent ---
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Для Windows нужно, чтобы gtest использовал тот же CRT, что и проект
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Ваш код (header-only: tmatrix.h) ---
add_library(matrix INTERFACE)
target_include_directories(matrix INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# --- Пример из samples (необязательно, но пусть собирается) ---
add_executable(sample_matrix samples/sample_matrix.cpp)
target_link_libraries(sample_matrix PRIVATE matrix)

# --- Тесты ---
add_executable(test_utmatrix
    test/test_tmatrix.cpp
    test/test_tvector.cpp
)

target_link_libraries(test_utmatrix PRIVATE
    matrix
    GTest::gtest_main
)

# Чтобы Visual Studio нашла тесты в обозревателе тестов
include(GoogleTest)
gtest_discover_tests(test_utmatrix)