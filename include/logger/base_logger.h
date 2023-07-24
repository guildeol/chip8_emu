#pragma once

#include <ostream>
#include <string>

namespace Logger
{
  enum class LogLevel
  {
    OFF,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
  };

  class BaseLogger
  {
    private:
      BaseLogger();

    protected:
      Logger::LogLevel level = Logger::LogLevel::INFO;
      std::ostream *infoStream;
      std::ostream *errStream;

    public:
      BaseLogger(Logger::LogLevel level, std::ostream *infoStream, std::ostream *errStream);

      void error(std::string msg);
      void warning(std::string msg);
      void info(std::string msg);
      void debug(std::string msg);
  };
}
