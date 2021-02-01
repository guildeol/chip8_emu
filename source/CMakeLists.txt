set (INCLUDE_PATH "../include")

set(HEADERS ${INCLUDE_PATH}/chip8.h ${INCLUDE_PATH}/cpu_specs.h)

set(SOURCES chip8.cpp)

add_library(chip8_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(chip8_lib PUBLIC ${INCLUDE_PATH})
