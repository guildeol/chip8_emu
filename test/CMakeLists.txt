set(GOOGLETEST_DIR "./googletest")

add_subdirectory(${GOOGLETEST_DIR})

add_executable(chip8_test main.cpp)

target_include_directories(chip8_test PUBLIC
                                            "${GOOGLETEST_DIR}/googletest/include/gtest"
                                            "${GOOGLETEST_DIR}/googlemock/include/gmock"
                          )


target_link_libraries(chip8_test PUBLIC
                                       gtest
                     )