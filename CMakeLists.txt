cmake_minimum_required(VERSION 3.24)
project(nox )

set(CMAKE_CXX_STANDARD 11)

add_executable(nox main.cpp)
find_library(LIB Dxva2)
target_link_libraries(nox ${LIB})
