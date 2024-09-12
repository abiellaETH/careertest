cmake_minimum_required(VERSION 3.29)
project(Part_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Part_1 main.cpp
        custom_hash.cpp
        custom_hash.h
        custom_doubly_linked_list.cpp
        custom_doubly_linked_list.h
)
