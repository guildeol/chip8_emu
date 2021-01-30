cmake_minimum_required(VERSION 3.18)

project(chip8_emu)

add_subdirectory(test)

add_executable(chip8 source/main.cpp)


