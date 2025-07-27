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
    LogLevel level = LogLevel::INFO;
    std::ostream *infoStream;
    std::ostream *errStream;
    std::string preamble;

  public:
    BaseLogger(Logger::LogLevel level, std::ostream *infoStream,
               std::ostream *errStream, std::string preamble);

    void error(std::string msg);
    void warning(std::string msg);
    void info(std::string msg);
    void debug(std::string msg);
  };
} // namespace Logger
