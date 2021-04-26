cmake_minimum_required(VERSION 3.10.2)

project("Triangle")

add_library(
        Triangle
        SHARED
        native-lib.cpp
        Triangle.hpp
        Triangle.cpp)

target_link_libraries(
        Triangle
        android
        EGL
        log
        GLESv2)