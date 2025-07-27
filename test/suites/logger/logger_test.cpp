#include <fmt/core.h>
#include <fmt/color.h>
#include <sstream>

#include "gtest/gtest.h"

#include "base_logger.h"

using namespace testing;

template<LogLevel compile_time_level>
class TestLogger : public BaseLogger<compile_time_level>
{
  public:
    std::stringstream info_stream;
    std::stringstream err_stream;

    TestLogger(const std::string &preamble = "") :
        BaseLogger<compile_time_level>(info_stream, err_stream, preamble)
    {
      // Empty
    }
};

TEST(LoggerTest, ShouldLogNothing)
{
  TestLogger<LogLevel::OFF> logger;

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.info_stream.str(), "");
  EXPECT_EQ(logger.err_stream.str(), "");
}

TEST(LoggerTest, ShouldLogError)
{
  auto logger = TestLogger<LogLevel::ERROR>();

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.info_stream.str(), "");
  EXPECT_EQ(logger.err_stream.str(), fmt::format(fg(fmt::color::red), "[ERROR] Error message\n"));
}
