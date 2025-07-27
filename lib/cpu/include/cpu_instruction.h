#pragma once

#include <bit>
#include <cstdint>

typedef union cpu_instruction_byte_field_u
{
  struct
  {
    uint8_t low  : 4;
    uint8_t high : 4;
  } nibble;

  uint8_t byte;
} cpu_instruction_byte_field_t;

/**
 * @brief Abstract type for CPU instructions.
 */
using cpu_instruction_raw_t = uint16_t;

/**
 * @brief Code for an invalid CPU Instruction.
 *
 */
constexpr cpu_instruction_raw_t CPU_INVALID_INSTRUCTION = 0xFFFF;

class CpuDecodedInstruction
{
public:
  cpu_instruction_byte_field_t fields[sizeof(cpu_instruction_raw_t)];

  CpuDecodedInstruction();
  CpuDecodedInstruction(cpu_instruction_raw_t raw);

  cpu_instruction_raw_t toRaw();
};
