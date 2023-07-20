set (INCLUDE_PATH "../include")

set(HEADERS
      ${INCLUDE_PATH}/cpu.h
      ${INCLUDE_PATH}/cpu_specs.h
      ${INCLUDE_PATH}/cpu_memory.h
      ${INCLUDE_PATH}/cpu_instruction.h
   )

set(SOURCES
      cpu.cpp
      cpu_memory.cpp
      cpu_instruction.cpp
   )

add_library(chip8_lib STATIC
              ${SOURCES}
              ${HEADERS}
           )

target_include_directories(chip8_lib PUBLIC ${INCLUDE_PATH})
