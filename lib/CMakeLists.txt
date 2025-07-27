add_library(chip8 STATIC)

add_subdirectory(cpu)

target_link_libraries(chip8 PUBLIC fmt::fmt)
