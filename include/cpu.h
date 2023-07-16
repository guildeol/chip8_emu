#pragma once

#include <string>

#include "cpu_specs.h"
#include "cpu_memory.h"

#include "errcodes.h"

class Cpu
{
    public:
        /**
         * @brief Construct a new Chip 8 object.
         */
        Cpu(CpuMemory &memory);

        /**
         * @brief Loads a given ROM into the system memory.
         *
         * @param[in] gameFile ROM to be loaded.
         *
         * @return Chip8ErrorCode_t.
         */
        Chip8ErrorCode_t loadGame(std::string gameFile);

    private:
      CpuMemory *memory;
};
