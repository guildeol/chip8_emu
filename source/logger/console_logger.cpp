#include <iostream>
#include <fmt/format.h>
#include <fmt/color.h>

#include "logger/base_logger.h"
#include "logger/console_logger.h"

Logger::ConsoleLogger::ConsoleLogger(Logger::LogLevel level) :
  BaseLogger(level, &std::cout, &std::cerr)
{

}

