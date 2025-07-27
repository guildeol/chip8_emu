#pragma once

#include <vector>

namespace Display
{
  using Dimension_t = unsigned int;
  using Coordinate_t = unsigned int;

  class BaseDisplay
  {
    public:
      virtual void clear() = 0;
      virtual void setPixel(Coordinate_t x, Coordinate_t y) = 0;
      virtual void clearPixel(Coordinate_t x, Coordinate_t y) = 0;
      virtual bool getPixelState(Coordinate_t x, Coordinate_t y) = 0;

    protected:
      Dimension_t nativeWidth;
      Dimension_t nativeHeight;

      Dimension_t emulatedWidth;
      Dimension_t emulatedHeight;
  };
} // namespace Display
