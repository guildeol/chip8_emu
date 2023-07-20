#pragma once

#include <cstdint>

/**
 * @brief  Size of the memory bank available for the emulator.
 */
constexpr uint16_t CPU_SPEC_MEMORY_BANK_B = 0x1000;

/**
 * @brief Memory offset of the intepreter in the emulator's memory bank.
 */
constexpr uint16_t CPU_SPEC_INTERPRETER_MEMORY_OFFSET_B = 0x0000;

/**
 * @brief Amount of memory reserved for the interpreter.
 */
constexpr uint16_t CPU_SPEC_INTERPRETER_MEMORY_LENGTH_B = 0x00200;

/**
 * @brief Memory offset of the built-in pixel font in the emulator's memory bank.
 *
 * @note This is located inside the interpreter memory region.
 */
constexpr uint16_t CPU_SPEC_FONT_MEMORY_OFFSET_B = 0x0050;

/**
 * @brief  Amount of memory reserved for the built-in pixel font.
 */
constexpr uint16_t CPU_SPEC_FONT_MEMORY_LENGTH_B = 0x0050;

/**
 * @brief Memory offset of the system ROM and work RAM in the emulator's memory bank.
 */
constexpr uint16_t CPU_SPEC_PROGRAM_ROM_WORK_RAM_OFFSET_B = 0x0200;

/**
 * @brief  Amount of memory reserved for the system ROM and work RAM.
 */
constexpr uint16_t CPU_SPEC_PROGRAM_ROM_WORK_RAM_LENGTH_B = 0x0800;

/**
 * @brief Number of V (aka General Purpose) registers in the system.
 */
constexpr uint16_t CPU_SPEC_GENERAL_V_COUNT = 16;
