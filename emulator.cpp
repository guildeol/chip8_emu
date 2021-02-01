#include <cstdint>
#include <cstdio>

#include <chip8.h>

using namespace std;

/**< Expected number of command line arguments. */
constexpr uint8_t _expectedArgCount = 2; // Program name + game file path
constexpr uint8_t _argvGameFilePosition = 1;

int main(int argc, char *argv[])
{
    Chip8 chip8;
    Chip8ErrorCode_t chip8Result;

    if (argc != _expectedArgCount)
    {
        printf("ERROR: %s arguments received!\n", argc > _expectedArgCount ? "Too many" : "Too few");
        return -1;
    }

    chip8Result = chip8.loadGame(argv[_argvGameFilePosition]);
    if (chip8Result != CHIP8_SUCCESS)
    {
        printf("ERROR: Failed to load gamefile %s\n", argv[_argvGameFilePosition]);
    }
    
    return 0;
}