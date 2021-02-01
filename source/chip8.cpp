#include <fstream>
#include <cstdio>

#include <chip8.h>

using namespace std;

Chip8::Chip8()
{
    memset(this->memory, 0x00, sizeof(this->memory));
}

Chip8ErrorCode_t Chip8::loadGame(std::string gameFile)
{
    fstream fileStream;
    
    fileStream.open(gameFile, (fstream::in | fstream::binary));

    if (!fileStream.good())
    {
        printf("ERROR: Could not open file %s\n", gameFile.c_str());
        return CHIP8_ERROR_LOADING;
    }

    fileStream.read(reinterpret_cast<char *>(this->workRam), CPU_SPEC_PROGRAM_ROM_WORK_RAM_LENGTH_B);

    if (fileStream.fail())
    {
        printf("ERROR: Could not read file %s\n", gameFile.c_str());
        return CHIP8_ERROR_LOADING;
    }

    // Everything went well, now the contents of gameFile are in the emulator's memory bank.

    return CHIP8_SUCCESS;
}
