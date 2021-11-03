cmake_minimum_required(VERSION 3.20)
project(collision)

set(CMAKE_CXX_STANDARD 14)

add_executable(collision main.cpp consts.h vec.h point.h line.h g2d.h)
