cmake_minimum_required(VERSION 3.9)
project(Dining_Philosophers C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(Dining_Philosophers dining-philosophers.c)
