cmake_minimum_required(VERSION 3.9)
project(sorting_multithread C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(sorting_multithread sorting-multithread.c)
