#include <iostream>
#include <fmt/format.h>
#include <fmt/color.h>

#include "logger/base_logger.h"

Logger::BaseLogger::BaseLogger(Logger::LogLevel level, std::ostream *infoStream, std::ostream *errStream):
  level(level),
  infoStream(infoStream),
  errStream(errStream)
{

}

void Logger::BaseLogger::error(std::string msg)
{
  if (this->level < Logger::LogLevel::ERROR)
    return;

  (*this->errStream) << fmt::format(fg(fmt::color::red), "[ERR]: {}", msg) << std::endl;
}

void Logger::BaseLogger::warning(std::string msg)
{
  if (this->level < Logger::LogLevel::WARNING)
    return;

  (*this->errStream) << fmt::format(fg(fmt::color::yellow), "[WRN]: {}", msg) << std::endl;
}

void Logger::BaseLogger::info(std::string msg)
{
  if (this->level < Logger::LogLevel::INFO)
    return;

  (*this->infoStream) << fmt::format(fg(fmt::color::green), "[INF]: {}", msg) << std::endl;
}

void Logger::BaseLogger::debug(std::string msg)
{
  if (this->level < Logger::LogLevel::DEBUG)
    return;

  (*this->infoStream) << fmt::format(fg(fmt::color::gray), "[DBG]: {}", msg) << std::endl;
}
