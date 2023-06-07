cmake_minimum_required(VERSION 3.24)
project(Snake)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
set(CMAKE_PREFIX_PATH /Users/jovialgang/Qt/5.15.14/clang_64)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(Snake
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Snake.pro
        Snake.pro.user)
target_link_libraries(Snake Qt5::Core Qt5::Widgets)