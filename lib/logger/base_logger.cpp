#include <iostream>
#include <fmt/format.h>
#include <fmt/color.h>

#include "logger/base_logger.h"

namespace Logger
{
  BaseLogger::BaseLogger(LogLevel level, std::ostream *infoStream, std::ostream *errStream, std::string preamble) :
    level(level),
    infoStream(infoStream),
    errStream(errStream),
    preamble(preamble)
  {
  }

  static void logMsg(std::ostream *stream, fmt::color color, std::string preamble, std::string lvl, std::string msg)
  {
    if (preamble.size() > 0)
      *stream << fmt::format(fg(color), "[{}][{}]: {}", preamble, lvl, msg) << std::endl;
    else
      *stream << fmt::format(fg(color), "[{}]: {}", lvl, msg) << std::endl;
  }

  void BaseLogger::error(std::string msg)
  {
    if (this->level < LogLevel::ERROR)
      return;

    logMsg(this->errStream, fmt::color::red, preamble, "ERR", msg);
  }

  void BaseLogger::warning(std::string msg)
  {
    if (this->level < LogLevel::WARNING)
      return;

    logMsg(this->errStream, fmt::color::yellow, preamble, "WRN", msg);
  }

  void BaseLogger::info(std::string msg)
  {
    if (this->level < LogLevel::INFO)
      return;

    logMsg(this->infoStream, fmt::color::green, preamble, "INF", msg);
  }

  void BaseLogger::debug(std::string msg)
  {
    if (this->level < LogLevel::DEBUG)
      return;

    logMsg(this->infoStream, fmt::color::gray, preamble, "DBG", msg);
  }
}
