#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

#include <cpu.h>

using namespace std;

Cpu::Cpu(CpuMemory &memory)
{
  this->memory = &memory;
}

Chip8ErrorCode_t Cpu::loadGame(std::string gameFile)
{
  fstream fileStream;

  fileStream.open(gameFile, (fstream::in | fstream::binary));
  if (!fileStream.good())
  {
    cerr << "ERROR: Could not open file " << gameFile << endl;
    return CHIP8_ERROR_LOADING;
  }

  fileStream.readsome(reinterpret_cast<char *>(this->memory->workRam), CPU_SPEC_PROGRAM_ROM_WORK_RAM_LENGTH_B);
  if (fileStream.fail())
  {
    printf("ERROR: Could not read file %s\n", gameFile.c_str());
    return CHIP8_ERROR_LOADING;
  }

  // Everything went well, now the contents of gameFile are in the emulator's memory bank.

  return CHIP8_SUCCESS;
}
