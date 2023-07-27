#include <iostream>
#include <fstream>
#include <bit>
#include <bitset>
#include <fmt/format.h>
#include <cstdio>
#include <cstring>

#include "cpu.h"
#include "logger/console_logger.h"

Logger::ConsoleLogger cpuLog = Logger::ConsoleLogger(Logger::LogLevel::DEBUG);

Cpu::Cpu()
{
  this->memory = std::make_unique<CpuMemory>();

  this->currentInstruction = CPU_INVALID_INSTRUCTION;
  this->decodedInstruction = CpuDecodedInstruction(CPU_INVALID_INSTRUCTION);
  this->V = std::vector<Register8>(16);
  this->pc = 0;
}

Cpu::Cpu(CpuMemory *memory_p = nullptr) :
  memory(memory_p)
{
  if(memory_p == nullptr)
    throw std::invalid_argument("Invalid CPU memory pointer");

  this->currentInstruction = CPU_INVALID_INSTRUCTION;
  this->decodedInstruction = CpuDecodedInstruction(CPU_INVALID_INSTRUCTION);
  this->V = std::vector<Register8>(16);
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

void Cpu::setDrawCallback(CpuDrawCallback_t callback)
{
  this->drawCallback = callback;
}

void Cpu::setClearCallback(CpuClearCallback_t callback)
{
  this->clearCallback = callback;
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

void Cpu::execute()
{
  auto NNN = this->currentInstruction & 0x0FFF;
  auto NN = this->currentInstruction & 0x00FF;
  auto N = this->currentInstruction & 0x000F;
  auto X = (this->currentInstruction & 0x0F00) >> 8;
  auto Y = (this->currentInstruction & 0x00F0) >> 4;
  std::vector<std::byte> drawBytes;
  int xDrawCoord;
  int yDrawCoord;

  switch (this->decodedInstruction.fields[0].nibble.high)
  {
    case 0x0:
      switch (this->decodedInstruction.fields[1].byte)
      {
        case 0xE0: // CLS
          this->clearCallback();
        break;

        case 0xEE:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "RET");
        break;

        default:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SYS $%03X", getNNN(instruction));
        break;
      }
    break;

    case 0x1: // JP NNN
      this->pc = NNN - CPU_SPEC_PROGRAM_ROM_WORK_RAM_OFFSET_B;
    break;

    case 0x2:
      cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
      // sprintf(mnemonic, "CALL $%03X", getNNN(instruction));
    break;

    case 0x3:
    cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
    //  sprintf(mnemonic, "SE V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0x4:
      cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
      // sprintf(mnemonic, "SNE V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0x5:
      switch (this->decodedInstruction.fields[1].nibble.low)
      {
        case 0x00:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SE V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        default:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }

    break;

    case 0x6: // LD VX, NN
      this->V[X] = NN;
    break;

    case 0x7: // ADD VX, NN
      this->V[X] += NN;
    break;

    case 0x8:
      switch (this->decodedInstruction.fields[1].nibble.low)
      {
        case 0x0:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x1:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "OR V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x2:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "AND V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x3:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "XOR V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x4:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "ADD V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x5:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SUB V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0x6:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SHR V%X", instruction.fields[0].nibble.low);
        break;

        case 0x7:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SUBN V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
        break;

        case 0xE:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SHR V%X", instruction.fields[0].nibble.low);
        break;

        default:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }
    break;

    case 0x9:
      cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
      // sprintf(mnemonic, "SNE V%X,V%X", instruction.fields[0].nibble.low, instruction.fields[1].nibble.high);
    break;

    case 0xA: // LD I
      this->I = NNN;
    break;

    case 0xB:
      cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
      // sprintf(mnemonic, "JP V0,$%03X", getNNN(instruction));
    break;

    case 0xC:
      cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
      // sprintf(mnemonic, "RND V%X,#%02X", instruction.fields[0].nibble.low, instruction.fields[1].byte);
    break;

    case 0xD: // DRW VX, VY, N
      drawBytes = this->memory->getBytes(this->I, N);

      this->V[0xF] = 0x00;
      yDrawCoord = this->V[Y];

      for (auto drawByte : drawBytes)
      {
        xDrawCoord = this->V[X];

        std::bitset<8> drawBitset(static_cast<uint8_t>(drawByte));
        bool wasOn = false;

        for (auto i : {7, 6, 5, 4, 3, 2, 1, 0})
        {
          if(drawBitset.test(i))
          {
            bool wasOn = this->drawCallback(xDrawCoord, yDrawCoord);

            if (wasOn)
              this->V[0xF] = 0x01;
          }

          xDrawCoord++;
        }

        yDrawCoord++;
      }
    break;

    case 0xE:
      switch (this->decodedInstruction.fields[1].byte)
      {
        case 0x9E:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SKP V%X", instruction.fields[0].nibble.low);
        break;

        case 0xA1:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "SKNP V%X", instruction.fields[0].nibble.low);
        break;

        default:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }
    break;

    case 0xF:
      switch (this->decodedInstruction.fields[1].byte)
      {
        case 0x07:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD V%X, DT", instruction.fields[0].nibble.low);
        break;

        case 0x0A:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD V%X, K", instruction.fields[0].nibble.low);
        break;

        case 0x15:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD DT, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x18:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD ST, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x1E:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "ADD I, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x29:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD F, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x33:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD B, V%X", instruction.fields[0].nibble.low);
        break;

        case 0x55:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD [I], V%X", instruction.fields[0].nibble.low);
        break;

        case 0x65:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "LD V%X, [I]", instruction.fields[0].nibble.low);
        break;

        default:
          cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
          // sprintf(mnemonic, "Invalid instruction 0x%04X", instruction.toRaw());
        break;
      }
    break;

    default:
      cpuLog.warning(fmt::format("Instruction {} not implemented yet!", this->currentInstruction));
      // sprintf(mnemonic, "Unknown instruction 0x%04X", instruction.toRaw());
    break;
  };
}
