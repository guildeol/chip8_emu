set (INCLUDE_PATH "../include")

set(HEADERS
      ${INCLUDE_PATH}/cpu.h
      ${INCLUDE_PATH}/cpu_specs.h
      ${INCLUDE_PATH}/cpu_memory.h
      ${INCLUDE_PATH}/cpu_instruction.h
      ${INCLUDE_PATH}/logger/base_logger.h
      ${INCLUDE_PATH}/logger/console_logger.h
      ${INCLUDE_PATH}/display/base_display.h
      ${INCLUDE_PATH}/display/sfml_display.h
   )

set(SOURCES
      cpu.cpp
      cpu_memory.cpp
      cpu_instruction.cpp
      logger/base_logger.cpp
      logger/console_logger.cpp
      display/sfml_display.cpp
   )

add_library(chip8_lib STATIC
              ${SOURCES}
              ${HEADERS}
           )

target_include_directories(chip8_lib PUBLIC ${INCLUDE_PATH})
target_link_libraries(chip8_lib PUBLIC fmt)
