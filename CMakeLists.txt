cmake_minimum_required(VERSION 3.18)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(chip8)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/libfmt.cmake)
# include(cmake/sfml.cmake)
# include(cmake/sdl.cmake)

# set(LIBS chip8_lib sfml-graphics sfml-window sfml-system)

add_subdirectory(lib)

add_subdirectory(test)
# add_subdirectory(source)

# add_executable(chip8_disassembler disassembler.cpp)
# target_include_directories(chip8_disassembler PUBLIC "include")
# target_link_libraries(chip8_disassembler PUBLIC chip8_lib)

# add_executable(chip8_emu emulator.cpp)
# target_include_directories(chip8_emu PUBLIC "include")
# target_link_libraries(chip8_emu PUBLIC ${LIBS})

# add_executable(chip8_display displayer.cpp)
# target_include_directories(chip8_display PUBLIC "include")
# target_link_libraries(chip8_display PUBLIC chip8_lib sfml-graphics sfml-window sfml-system)
