#include <iostream>
#include <fmt/format.h>
#include <fmt/color.h>

#include "logger/base_logger.h"
#include "logger/console_logger.h"

namespace Logger
{
  ConsoleLogger::ConsoleLogger(LogLevel level, std::string preamble) :
    BaseLogger(level, &std::cout, &std::cerr, preamble)
  {

  }
}

