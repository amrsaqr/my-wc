cmake_minimum_required(VERSION 3.28)
project(my_wc)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_wc
        src/main.cpp
        src/args_reader.h
        src/args_reader.cpp
        src/counter.cpp
        src/counter.h)
