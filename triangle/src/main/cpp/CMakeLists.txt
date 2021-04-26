cmake_minimum_required(VERSION 3.10.2)

project("Triangle")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

add_library(
        Triangle
        SHARED
        native-lib.cpp
        nanovg.c
        Triangle.cpp)

target_link_libraries(
        Triangle
        android
        EGL
        log
        GLESv2)