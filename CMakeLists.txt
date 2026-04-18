cmake_minimum_required(VERSION 3.16)
project(cpp_autodiff LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(demo
    src/main.cpp
    src/value.cpp
)

target_include_directories(demo PRIVATE src)