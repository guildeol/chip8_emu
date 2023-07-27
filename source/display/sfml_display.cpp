#include <algorithm>
#include <thread>
#include <fmt/format.h>

#include "logger/console_logger.h"
#include "display/sfml_display.h"

static Logger::ConsoleLogger sfmlDisplayLog(Logger::LogLevel::INFO, "sfml_display");

namespace Display
{
  SfmlDisplay::SfmlDisplay(Dimension_t nativeWidth, Dimension_t nativeHeight,
                           Dimension_t emulatedWidth, Dimension_t emulatedHeight) : window(sf::RenderWindow(sf::VideoMode(nativeWidth, nativeHeight), "Chip8 - SFML"))
  {
    this->nativeWidth = nativeWidth;
    this->nativeHeight = nativeHeight;
    this->emulatedWidth = emulatedWidth;
    this->emulatedHeight = emulatedHeight;

    try
    {
      this->pixels = std::vector<SfmlDisplay::sfml_pixel_s>(this->emulatedWidth * this->emulatedHeight);

      sfmlDisplayLog.info(fmt::format("Initialized display with {} fake pixels", this->pixels.size()));

      for (auto i = 0; i < this->pixels.size(); i++)
      {
        auto xCoord = i % this->emulatedWidth;
        auto yCoord = i / this->emulatedWidth;

        auto &entry = this->pixels.at(i);
        auto xScale = this->nativeWidth / this->emulatedWidth;
        auto yScale = this->nativeHeight / this->emulatedHeight;

        entry.isOn = false;
        entry.shape = sf::RectangleShape(sf::Vector2f(1.0f * xScale, 1.0f * yScale));

        entry.shape.setPosition(sf::Vector2f(xCoord * xScale, yCoord * yScale));

        sfmlDisplayLog.debug(fmt::format("Initialized pixel {} at coords [{}, {}]", i, entry.shape.getPosition().x,
                                                                                      entry.shape.getPosition().y));
      }

      this->isOpen = true;
    }
    catch (const std::exception &e)
    {
      sfmlDisplayLog.error(fmt::format("Failed to initialize fake pixel array: {}", e.what()));
      throw e;
    }
  }
  void SfmlDisplay::update()
  {
    this->isOpen = this->window.isOpen();
    if (!this->isOpen)
      return;

    sf::RectangleShape test(sf::Vector2f(20, 20));

    sf::Event event;
    while (this->window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        this->window.close();

      this->window.clear();

      for (auto &entry : this->pixels)
      {
        if (entry.isOn)
          this->window.draw(entry.shape);
      }

      this->window.display();
    }
  }

  void SfmlDisplay::clear()
  {
    for (auto &entry : this->pixels)
      entry.isOn = false;

    sfmlDisplayLog.debug(fmt::format("Cleared scren!"));
  }

  void SfmlDisplay::setPixel(Coordinate_t x, Coordinate_t y)
  {
    x = x % this->emulatedWidth;
    y = y % this->emulatedHeight;

    auto &p = this->pixels.at(x + (y * this->emulatedWidth));

    p.isOn = true;

    sfmlDisplayLog.info(fmt::format("Pixel[{}, {}] @ [{}, {}] is ON", x, y, p.shape.getPosition().x,
                         p.shape.getPosition().y));
  }

  void SfmlDisplay::clearPixel(Coordinate_t x, Coordinate_t y)
  {
    x = x % this->emulatedWidth;
    y = y % this->emulatedHeight;

    auto &p = this->pixels.at(x + (y * this->emulatedWidth));

    p.isOn = false;

    sfmlDisplayLog.info(fmt::format("Pixel[{}, {}] @ [{}, {}] is OFF", x, y, p.shape.getPosition().x,
                         p.shape.getPosition().y));
  }

  bool SfmlDisplay::getPixelState(Coordinate_t x, Coordinate_t y)
  {
    x = x % this->emulatedWidth;
    y = y % this->emulatedHeight;

    auto p = this->pixels.at(x + (y * this->emulatedWidth));

    return p.isOn;
  }
}
