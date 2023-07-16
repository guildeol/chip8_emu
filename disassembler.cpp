#include <iostream>
#include <cstdint>
#include <cstdio>

#include "cpu.h"

/**< Expected number of command line arguments. */
constexpr uint8_t _expectedArgCount = 2; // Program name + game file path
constexpr uint8_t _argvGameFilePosition = 1;

void disassemble(cpu_instruction_t)
{
  return;
}

int main(int argc, char *argv[])
{
  CpuMemory memory;
  Cpu chip8 = Cpu(&memory);

  chip8_error_code_t chip8Result;

  if (argc != _expectedArgCount)
  {
    printf("ERROR: %s arguments received!\n", argc > _expectedArgCount ? "Too many" : "Too few");
    return -1;
  }

  chip8Result = chip8.loadGame(argv[_argvGameFilePosition]);
  if (chip8Result != CHIP8_SUCCESS)
  {
    printf("ERROR: Failed to load gamefile %s\n", argv[_argvGameFilePosition]);
    return -1;
  }

  for (size_t i = 0; i < memory.workRam.size; i++)
  {
    cpu_instruction_t instruction = chip8.fetch();

    disassemble(instruction);
  }

  return 0;
}
