#include <iostream>

#include <cstdint>
#include <cstdio>

#include "cpu.h"

/**< Expected number of command line arguments. */
constexpr uint8_t _expectedArgCount = 2; // Program name + game file path
constexpr uint8_t _argvGameFilePosition = 1;

std::string disassemble(CpuDecodedInstruction instruction)
{
  char mnemonic[100];

  auto getAddress = [](CpuDecodedInstruction i)
  {
    return i.toRaw() & 0xFFF;
  };

  switch (instruction.fields[0].nibble.high)
  {
    case 0x0:
      switch (instruction.fields[1].byte)
      {
        case 0xE0:
          sprintf(mnemonic, "CLS");
        break;

        case 0xEE:
          sprintf(mnemonic, "RET");
        break;

        default:
          sprintf(mnemonic, "SYS $%03X", getAddress(instruction));
        break;
      }
    break;

    case 0x1:
      sprintf(mnemonic, "JP $%03X", getAddress(instruction));
    break;

    case 0x2:
      sprintf(mnemonic, "CALL $%03X", getAddress(instruction));
    break;

    case 0x3:
     sprintf(mnemonic, "SE V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0x4:
      sprintf(mnemonic, "SNE V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0x5:
      switch (instruction.fields[1].nibble.low)
      {
        case 0x00:
          sprintf(mnemonic, "SE V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        default:
          sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }

    break;

    case 0x6:
      sprintf(mnemonic, "LD V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0x7:
      sprintf(mnemonic, "ADD V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0x8:
      switch (instruction.fields[1].nibble.low)
      {
        case 0x0:
          sprintf(mnemonic, "LD V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x1:
          sprintf(mnemonic, "OR V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x2:
          sprintf(mnemonic, "AND V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x3:
          sprintf(mnemonic, "XOR V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x4:
          sprintf(mnemonic, "ADD V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x5:
          sprintf(mnemonic, "SUB V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x6:
          sprintf(mnemonic, "SHR V%X", instruction.fields[0].nibble.low);
        break;

        case 0x7:
          sprintf(mnemonic, "SUBN V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0xE:
          sprintf(mnemonic, "SHR V%X", instruction.fields[0].nibble.low);
        break;

        default:
          sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }
    break;

    case 0x9:
      sprintf(mnemonic, "SNE V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
    break;

    case 0xA:
      sprintf(mnemonic, "LD I,$%03X", getAddress(instruction));
    break;

    case 0xB:
      sprintf(mnemonic, "JP V0,$%03X", getAddress(instruction));
    break;

    case 0xC:
      sprintf(mnemonic, "RND V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0xD:
      sprintf(mnemonic, "DRW V%X,V%X,#%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high,instruction.fields[1].nibble.low);
    break;

    case 0xE:
      switch (instruction.fields[1].byte)
      {
        case 0x9E:
          sprintf(mnemonic, "SKP V%X", instruction.fields[0].nibble.low);
        break;

        case 0xA1:
          sprintf(mnemonic, "SKNP V%X", instruction.fields[0].nibble.low);
        break;

        default:
          sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }
    break;

    case 0xF:
      switch (instruction.fields[1].byte)
      {
        case 0x07:
          sprintf(mnemonic, "LD V%X, DT", instruction.fields[0].nibble.low);
        break;

        case 0x0A:
          sprintf(mnemonic, "LD V%X, K", instruction.fields[0].nibble.low);
        break;

        case 0x15:
          sprintf(mnemonic, "LD DT, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x18:
          sprintf(mnemonic, "LD ST, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x1E:
          sprintf(mnemonic, "ADD I, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x29:
          sprintf(mnemonic, "LD F, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x33:
          sprintf(mnemonic, "LD B, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x55:
          sprintf(mnemonic, "LD [I], V%X", instruction.fields[0].nibble.low);
        break;

        case 0x65:
          sprintf(mnemonic, "LD V%X, [I]", instruction.fields[0].nibble.low);
        break;

        default:
          sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }
    break;

    default:
      sprintf(mnemonic, "Unknown instruction 0x%04X", instruction.toRaw());
    break;
  };

  return std::string(mnemonic);
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
    chip8.fetch();
    chip8.decode();

    std::cout << std::hex << (0x200 + i) << " ";
    std::cout << disassemble(chip8.decodedInstruction);
    std::cout << std::endl;
  }

  return 0;
}
