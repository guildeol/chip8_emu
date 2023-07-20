cmake_minimum_required(VERSION 3.18)

project(chip8_emu)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(test)
add_subdirectory(source)

add_executable(chip8_disassembler disassembler.cpp)
target_include_directories(chip8_disassembler PUBLIC "include")
target_link_libraries(chip8_disassembler PUBLIC chip8_lib)

add_executable(chip8_emu emulator.cpp)
target_include_directories(chip8_emu PUBLIC "include")
target_link_libraries(chip8_emu PUBLIC chip8_lib)

