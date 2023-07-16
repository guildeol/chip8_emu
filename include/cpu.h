#pragma once

#include <string>
#include <memory>

#include "cpu_specs.h"
#include "cpu_memory.h"

#include "errcodes.h"

class CpuException : public std::exception
{
  private:
    std::string message;

  public:
    CpuException(std::string msg)
    {
      this->message = msg;
    }

    const char * what ()
    {
        return this->message.c_str();
    }
};

class Cpu
{
  private:
    size_t pc;
    std::unique_ptr<CpuMemory> memory = nullptr;

  public:
    /**
     * @brief Construct a new Cpu object
     */
    Cpu();

    /**
     * @brief Construct a new Cpu object
     *
     * @param[in] memory_p Pointer to a CpuMemory object.
     */
    Cpu(CpuMemory *memory_p);

    /**
     * @brief Loads a given ROM into the system memory.
     *
     * @param[in] gameFile ROM to be loaded.
     *
     * @return chip8_error_code_t.
     */
    chip8_error_code_t loadGame(std::string gameFile);

    cpu_instruction_t fetch();
};
