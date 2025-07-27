#include <fmt/core.h>
#include <fmt/color.h>
#include <string>

#include "gtest/gtest.h"

#include "base_logger.h"

using namespace testing;

template<LogLevel log_level>
class TestLogger : public BaseLogger<TestLogger<log_level>, log_level>
{
  public:
    std::string out;
    std::string err;

    TestLogger(const std::string &preamble = {}) :
        BaseLogger<TestLogger, log_level>(preamble)
    {
      // Empty
    }

    void standard_output(const std::string &message)
    {
      this->out += message;
    }

    void error_output(const std::string &message)
    {
      this->err += message;
    }
};

TEST(LoggerTest, ShouldLogNothing)
{
  TestLogger<LogLevel::OFF> logger;

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.out, "");
  EXPECT_EQ(logger.err, "");
}

TEST(LoggerTest, ShouldLogError)
{
  auto logger = TestLogger<LogLevel::ERROR>();

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.out, "");
  EXPECT_EQ(logger.err, fmt::format(fg(fmt::color::red), "[ERROR] Error message\n"));
}
