#pragma once

#include <array>
#include <vector>
#include <stdexcept>

#include "cpu_specs.h"

typedef struct CpuMemoryRegion_s
{
  std::byte * const start;
  size_t length;
  size_t size;
} CpuMemoryRegion_t;

class CpuMemory
{
private:
  /**
   * @brief Represents the system's whole memory bank.
   */
  std::array<std::byte, CPU_SPEC_MEMORY_BANK_B> bank;

public:
  CpuMemory();
  std::vector<std::byte> getBytes(size_t offset, size_t count);

  /**
   * @brief Pointer to the memory region reserved for the system's work RAM.
   */
  CpuMemoryRegion_t workRam =
  {
    .start = &bank[CPU_SPEC_PROGRAM_ROM_WORK_RAM_OFFSET_B],
    .length = CPU_SPEC_PROGRAM_ROM_WORK_RAM_LENGTH_B,
    .size = 0,
  };

  CpuMemoryRegion_t font =
  {
    .start = &bank[CPU_SPEC_FONT_MEMORY_OFFSET_B],
    .length = CPU_SPEC_FONT_MEMORY_LENGTH_B,
    .size = 0,
  };
};
