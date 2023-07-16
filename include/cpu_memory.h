#pragma once

#include <cstddef>

#include "cpu_specs.h"

class CpuMemory
{
private:
  /**
   * @brief Represents the system's whole memory bank.
   */
  std::byte bank[CPU_SPEC_MEMORY_BANK_B];

public:
  CpuMemory();

  /**
   * @brief Pointer to the memory region reserved for the system's work RAM.
   */
  std::byte *const workRam = &(bank[CPU_SPEC_PROGRAM_ROM_WORK_RAM_OFFSET_B]);
};
