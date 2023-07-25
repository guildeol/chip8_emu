#pragma once

#include "logger/base_logger.h"

namespace Logger
{
  class ConsoleLogger : public BaseLogger
  {
    public:
      ConsoleLogger(LogLevel level, std::string preamble = "");
  };
}
