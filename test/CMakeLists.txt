include(../cmake/googletest.cmake)

add_executable(chip8_test main.cpp)

target_include_directories(chip8_test PUBLIC)

target_link_libraries(chip8_test PUBLIC chip8 gtest gmock fmt::fmt)

# Glob all .c and .cpp files
file(GLOB TEST_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp"
)

target_sources(chip8_test PUBLIC suites/logger/logger_test.cpp)
