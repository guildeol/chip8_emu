set(GOOGLETEST_DIR "./googletest")

add_subdirectory(${GOOGLETEST_DIR})

add_executable(chip8_test main.cpp)

target_include_directories(chip8_test PUBLIC
                            ${GOOGLETEST_DIR}/googlemock/include
                            ${GOOGLETEST_DIR}/googletest/include
                            ${CMAKE_HOME_DIRECTORY}/include
                          )


target_link_libraries(chip8_test PUBLIC
                        gtest
                        fmt
                     )

target_sources(chip8_test PUBLIC
                suites/CPU/cpu_test.cpp
                suites/logger/logger_test.cpp
                ${CMAKE_HOME_DIRECTORY}/source/cpu.cpp
                ${CMAKE_HOME_DIRECTORY}/source/cpu_memory.cpp
                ${CMAKE_HOME_DIRECTORY}/source/cpu_instruction.cpp
                ${CMAKE_HOME_DIRECTORY}/source/logger/base_logger.cpp
                ${CMAKE_HOME_DIRECTORY}/source/logger/console_logger.cpp
              )
