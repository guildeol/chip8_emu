#pragma once

#include <string>
#include <cpu_specs.h>

/**
 * @brief Possible errors returned by class Chip8.
 */
typedef enum Chip8ErrorCode_t_
{
    CHIP8_SUCCESS = 0,
    CHIP8_ERROR_LOADING,
} Chip8ErrorCode_t;

class Chip8
{
    public:
        /**
         * @brief Construct a new Chip 8 object.
         */
        Chip8();

        /**
         * @brief Loads a given ROM into the system memory.
         * 
         * @param[in] gameFile ROM to be loaded.
         * 
         * @return Chip8ErrorCode_t.
         */
        Chip8ErrorCode_t loadGame(std::string gameFile);

    private:
        /**
         * @brief Represents the system's whole memory bank.
         */
        uint8_t memory[CPU_SPEC_MEMORY_BANK_B]; 

        /**
         * @brief Pointer to the memory region reserved for the system's work RAM.
         */
        uint8_t * const workRam = &(memory[CPU_SPEC_PROGRAM_ROM_WORK_RAM_OFFSET_B]);
};
