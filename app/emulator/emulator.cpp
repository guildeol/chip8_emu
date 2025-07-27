#include <cstdint>
#include <cstdio>

#include "cpu.h"
#include "display/sfml_display.h"

/**< Expected number of command line arguments. */
constexpr uint8_t _expectedArgCount = 2; // Program name + game file path
constexpr uint8_t _argvGameFilePosition = 1;

constexpr Display::Dimension_t nativeWidth = 1280;
constexpr Display::Dimension_t nativeHeight = 640;
constexpr Display::Dimension_t emulatedWidth = 64;
constexpr Display::Dimension_t emulatedHeight = 32;

Display::SfmlDisplay display = Display::SfmlDisplay(nativeWidth, nativeHeight, emulatedWidth, emulatedHeight);

void emulatorClearScreenCallback()
{
  display.clear();
}

bool emulatorDrawPixelCallback(int xCoord, int yCoord)
{
  bool wasOn = false;
  bool pixelState = display.getPixelState(xCoord, yCoord) == true;

  if (pixelState == true)
    wasOn = true;

  if (pixelState ^ true)
    display.setPixel(xCoord, yCoord);
  else
    display.clearPixel(xCoord, yCoord);

  return wasOn;
}

int main(int argc, char *argv[])
{
  Cpu chip8;
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

  chip8.setClearCallback(emulatorClearScreenCallback);
  chip8.setDrawCallback(emulatorDrawPixelCallback);

  while (display.isOpen)
  {
    chip8.fetch();
    chip8.decode();
    chip8.execute();

    display.update();
  }

  return 0;
}
