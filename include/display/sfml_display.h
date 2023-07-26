#pragma once

#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "display/base_display.h"

namespace Display
{
  class SfmlDisplay : public BaseDisplay
  {
    public:
      bool isOpen;

      SfmlDisplay(Dimension_t nativeWidth, Dimension_t nativeHeight,
                  Dimension_t emulatedWidth, Dimension_t emulatedHeight);
      void update();
      void clear();
      void setPixel(Coordinate_t x, Coordinate_t y);
      void clearPixel(Coordinate_t x, Coordinate_t y);
    private:
      struct sfml_pixel_s
      {
        sf::RectangleShape shape;
        bool isOn;
      };

      sf::RenderWindow window;
      std::vector<struct sfml_pixel_s> pixels;
  };
};
