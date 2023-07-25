#include <cstdint>
#include <cstdio>

#include "display/sfml_display.h"

int main()
{
  Display::SfmlDisplay sfmlDisplay = Display::SfmlDisplay(1280, 640, 20);

  return 0;
}
