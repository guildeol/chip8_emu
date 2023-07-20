#include "cpu_instruction.h"

CpuDecodedInstruction::CpuDecodedInstruction(cpu_instruction_raw_t raw)
{
  this->fields[1].byte = raw & 0xFF;
  this->fields[0].byte = (raw >> 8) & 0xFF;
}

cpu_instruction_raw_t CpuDecodedInstruction::toRaw()
{
  return (this->fields[0].byte << 8) | (this->fields[1].byte);
}
