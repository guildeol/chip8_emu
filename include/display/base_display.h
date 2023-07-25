#pragma once

#include <vector>

namespace Display
{
  using Dimension_t = unsigned int;
  using Coordinate_t = unsigned int;
  using PixelState_t = bool;

  class BaseDisplay
  {
    public:
      virtual void clear() = 0;
      virtual void setPixel(Coordinate_t x, Coordinate_t y) = 0;

    protected:
      Dimension_t width;
      Dimension_t height;
      Dimension_t scale;
      std::vector<PixelState_t> pixels;
  };
}
