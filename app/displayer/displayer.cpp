#include <cstdint>
#include <cstdio>

#include "display/sfml_display.h"

int main()
{
  Display::SfmlDisplay display = Display::SfmlDisplay(1280, 640, 64, 32);

  display.setPixel(0, 0);
  display.setPixel(0, 1);
  display.setPixel(0, 2);
  display.setPixel(0, 3);

  while (display.isOpen)
  {
    display.update();
  }

  return 0;
}
