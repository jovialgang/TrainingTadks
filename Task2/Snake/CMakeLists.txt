cmake_minimum_required(VERSION 3.24)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Snake
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Snake.pro
        Snake.pro.user)
