#include <cstring>

#include "cpu_memory.h"

CpuMemory::CpuMemory()
{
  memset(this->bank, 0x00, sizeof(this->bank));
}
