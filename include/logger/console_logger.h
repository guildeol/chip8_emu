#pragma once

#include "logger/base_logger.h"

namespace Logger
{
  class ConsoleLogger : public Logger::BaseLogger
  {
    public:
      ConsoleLogger(Logger::LogLevel level);
  };
}
