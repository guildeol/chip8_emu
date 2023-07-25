#include <algorithm>
#include <thread>
#include <fmt/format.h>

#include "logger/console_logger.h"
#include "display/sfml_display.h"

static Logger::ConsoleLogger sfmlDisplayLog(Logger::LogLevel::DEBUG, "sfml_display");

namespace Display
{
  SfmlDisplay::SfmlDisplay(Dimension_t width, Dimension_t height, Dimension_t scale) :
    window(sf::RenderWindow(sf::VideoMode(width, height), "Chip8 - SFML"))
  {
    this->width = width;
    this->height = height;
    this->scale = scale;

    try
    {
      this->fakePixels = std::vector<SfmlDisplay::fake_pixel_s>((this->width / this->scale) * (this->height / this->scale));

      sfmlDisplayLog.info(fmt::format("Initialized display with {} fake pixels", this->fakePixels.size()));

      for (auto i = 0; i < this->fakePixels.size(); i++)
      {
        auto entry = this->fakePixels.at(i);

        entry.isOn = false;
        entry.shape = sf::RectangleShape(sf::Vector2f(1.0f * this->scale, 1.0f * this->scale));

        auto newX = (i * this->scale) % this->width;
        auto newY = (i * this->scale) % this->height;

        sfmlDisplayLog.info(fmt::format("Initialized pixel {} at coords [{}, {}]", i, newX, newY));

        // entry.shape.setPosition();
      }
    }
    catch (const std::exception &e)
    {
      sfmlDisplayLog.error(fmt::format("Failed to initialize fake pixel array: {}", e.what()));
      throw e;
    }
  }


  void SfmlDisplay::clear()
  {
    return;
  }

  void SfmlDisplay::setPixel(Coordinate_t x, Coordinate_t y)
  {
    return;
  }

}
