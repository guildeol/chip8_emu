#pragma once

#include <cstdio>
#include <string_view>

enum class LogLevel
{
  OFF,
  ERROR,
  WARNING,
  INFO,
  DEBUG,
};

template <LogLevel compile_time_level>
class BaseLogger
{
    const std::string preamble;

    BaseLogger();

    const char *level_to_string(LogLevel level) const
    {
      // clang-format off
      switch (level)
      {
        case LogLevel::OFF:     return "OFF";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::DEBUG:   return "DEBUG";
        default:                return "UNKNOWN";
      }
      // clang-format on
    }

    template <typename... Args>
    void log(LogLevel p_level, const char *p_fmt_msg, Args &&...p_args)
    {
      std::array<char, 256> message;
      if (this->preamble.empty())
      {
        snprintf(message.data(), message.size(), "[%s] %s\n", level_to_string(p_level), p_fmt_msg, std::forward<Args>(p_args)...);
      }
      else
      {
        snprintf(message.data(), message.size(), "[%s][%s] %s\n", this->preamble.c_str(), level_to_string(p_level), p_fmt_msg,
                 std::forward<Args>(p_args)...);
      }

      if (p_level == LogLevel::ERROR || p_level == LogLevel::WARNING)
      {
        this->error_output(message.data());
      }
      else
      {
        this->standard_output(message.data());
      }
    }

    virtual void error_output(const std::string_view message) = 0;
    virtual void standard_output(const std::string_view message) = 0;

  protected:
    BaseLogger(const std::string &preamble = "") : preamble(preamble)
    {
      // Empty
    }

  public:
    template <typename... Args>
    void error(const char *p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::ERROR)
      {
        log(LogLevel::ERROR, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }

    template <typename... Args>
    void warning(const char *p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::WARNING)
      {
        log(LogLevel::WARNING, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }

    template <typename... Args>
    void info(const char *p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::INFO)
      {
        log(LogLevel::INFO, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }

    template <typename... Args>
    void debug(const char *p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::DEBUG)
      {
        log(LogLevel::DEBUG, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }
};
