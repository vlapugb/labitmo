cmake_minimum_required(VERSION 3.0)

project(MyProject)

set(SOURCES
    src/main.cpp
    src/header.hpp
)

add_executable(my_executable ${SOURCES})
