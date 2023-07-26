#include <iostream>
#include <fstream>
#include <bit>
#include <bitset>
#include <cstdio>
#include <cstring>

#include <cpu.h>

Cpu::Cpu()
{
  this->memory = std::make_unique<CpuMemory>();

  this->currentInstruction = CPU_INVALID_INSTRUCTION;
  this->decodedInstruction = CpuDecodedInstruction(CPU_INVALID_INSTRUCTION);
  this->pc = 0;
}

Cpu::Cpu(CpuMemory *memory_p = nullptr) :
  memory(memory_p)
{
  if(memory_p == nullptr)
    throw std::invalid_argument("Invalid CPU memory pointer");

  this->pc = 0;
}

chip8_error_code_t Cpu::loadGame(std::string gameFile)
{
  std::fstream fileStream;

  fileStream.open(gameFile, (std::fstream::in | std::fstream::binary));
  if (!fileStream.good())
  {
    return CHIP8_ERROR_LOADING;
  }

  this->memory->workRam.size = fileStream.readsome(reinterpret_cast<char *>(this->memory->workRam.start),
                                                   this->memory->workRam.length);
  if (fileStream.fail())
  {
    return CHIP8_ERROR_LOADING;
  }

  // Everything went well, now the contents of gameFile are in the emulator's memory bank.

  return CHIP8_SUCCESS;
}

void Cpu::fetch()
{
  if (this->memory == nullptr)
    throw CpuException("Memory uninitialized");

  if (this->pc >= this->memory->workRam.size)
    throw CpuException("Out of instructions!");

  this->currentInstruction = *reinterpret_cast<cpu_instruction_raw_t *>(&this->memory->workRam.start[this->pc]);
  this->currentInstruction = std::rotr(this->currentInstruction, 8);

  this->pc += sizeof(cpu_instruction_raw_t);
}

void Cpu::decode()
{
  this->decodedInstruction = CpuDecodedInstruction(this->currentInstruction);
}
