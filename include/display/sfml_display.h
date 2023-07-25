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
      SfmlDisplay(Dimension_t width, Dimension_t height, Dimension_t scale);
      void clear();
      void setPixel(Coordinate_t x, Coordinate_t y);

    private:
      struct fake_pixel_s
      {
        sf::RectangleShape shape;
        bool isOn;
      };

      sf::RenderWindow window;
      std::vector<struct fake_pixel_s> fakePixels;
  };
};
