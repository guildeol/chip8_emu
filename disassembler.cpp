#include <iostream>
#include <sstream>
#include <iomanip>

#include <cstdint>
#include <cstdio>

#include "cpu.h"

/**< Expected number of command line arguments. */
constexpr uint8_t _expectedArgCount = 2; // Program name + game file path
constexpr uint8_t _argvGameFilePosition = 1;

std::stringstream disassemble(CpuDecodedInstruction instruction)
{
  std::stringstream mnemonic;

  mnemonic.setf(std::ios_base::hex, std::ios_base::basefield);

  switch (instruction.fields[0].byte)
  {
    case 0x00:
      if (instruction.fields[1].byte == 0xE0)
      {
        mnemonic << "CLS";
      }
      else
      {
        mnemonic << "Unsupported instruction 0x" << std::setw(4) << std::setfill('0') << instruction.toRaw();
      }
    break;

    default:
      mnemonic << "Unsupported instruction 0x" << std::setw(4) << std::setfill('0') << instruction.toRaw();
    break;
  };

  return mnemonic;
}

int main(int argc, char *argv[])
{
  CpuMemory *memory = new CpuMemory();
  Cpu chip8 = Cpu(memory);

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

  for (size_t i = 0; i < memory->workRam.size; i += 2)
  {
    cpu_instruction_raw_t instruction = chip8.fetch();

    std::cout << std::hex << (0x200 + i) << " ";
    std::cout << disassemble(instruction).str();
    std::cout << std::endl;
  }

  return 0;
}
