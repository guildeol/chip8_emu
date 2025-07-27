target_include_directories(chip8 PUBLIC ./include)

target_sources(chip8 PRIVATE
    ./cpu.cpp
    ./cpu_instruction.cpp
    ./cpu_memory.cpp
)
