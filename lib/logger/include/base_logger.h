#pragma once

#include <fmt/color.h>
#include <fmt/format.h>
#include <ostream>
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
  private:
    const LogLevel level;
    const std::string preamble;
    std::ostream &info_stream;
    std::ostream &err_stream;

    BaseLogger();

    constexpr const char *level_to_string(LogLevel level) const
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
    void log(LogLevel p_level, const fmt::color p_color, const fmt::format_string<Args...> p_fmt_msg, Args &&...p_args)
    {
      auto &out_stream = (p_level == LogLevel::ERROR || p_level == LogLevel::WARNING) ? err_stream : info_stream;
      auto log_line = fmt::format(p_fmt_msg, std::forward<Args>(p_args)...);

      if (preamble.empty())
      {
        out_stream << fmt::format(fg(p_color), "[{}] {}\n", level_to_string(p_level), log_line);
      }
      else
      {
        out_stream << fmt::format(fg(p_color), "[{}][{}] {}\n", this->preamble, level_to_string(p_level), log_line);
      }
    }

  protected:
    BaseLogger(std::ostream &info_stream, std::ostream &err_stream, const std::string &preamble = "")
        : level(level), preamble(preamble), info_stream(info_stream), err_stream(err_stream)
    {
      // Empty
    }

  public:
    template <typename... Args>
    void error(const fmt::format_string<Args...>  p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::ERROR)
      {
        log(LogLevel::ERROR, fmt::color::red, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }

    template <typename... Args>
    void warning(const fmt::format_string<Args...>  p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::WARNING)
      {
        log(LogLevel::WARNING, fmt::color::yellow, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }

    template <typename... Args>
    void info(const fmt::format_string<Args...>  p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::INFO)
      {
        log(LogLevel::INFO, fmt::color::blue, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }

    template <typename... Args>
    void debug(const fmt::format_string<Args...>  p_fmt_msg, Args &&...p_args)
    {
      if constexpr (compile_time_level >= LogLevel::DEBUG)
      {
        log(LogLevel::DEBUG, fmt::color::green, p_fmt_msg, std::forward<Args>(p_args)...);
      }
    }
};
