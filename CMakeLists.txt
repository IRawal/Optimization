cmake_minimum_required(VERSION 3.26)
project(optimization)

set(CMAKE_CXX_STANDARD 17)

add_executable(optimization main.cpp
        Genetic.cpp
        Genetic.h)
