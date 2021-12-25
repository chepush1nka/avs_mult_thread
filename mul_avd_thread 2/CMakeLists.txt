cmake_minimum_required(VERSION 3.20)
project(mul_avd_thread)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS -pthread)

add_executable(mul_avd_thread main.cpp container.cpp container.h)
