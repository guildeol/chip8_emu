#include <string>

#include "gtest/gtest.h"

#include "base_logger.h"

using namespace testing;

template <LogLevel log_level>
class TestLogger : public BaseLogger<log_level>
{
  public:
    std::string out; // NOLINT(misc-non-private-member-variables-in-classes)
    std::string err; // NOLINT(misc-non-private-member-variables-in-classes)

    TestLogger(const std::string &preamble = {}) : BaseLogger<log_level>(preamble)
    {
      // Empty
    }

    void standard_output(const std::string_view message) override { this->out += message; }

    void error_output(const std::string_view message) override { this->err += message; }
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
  EXPECT_EQ(logger.err, "[ERROR] Error message\n");
}

TEST(LoggerTest, ShouldLogWarningAndError)
{
  auto logger = TestLogger<LogLevel::WARNING>();

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.out, "");
  EXPECT_EQ(logger.err, "[WARNING] Warning message\n[ERROR] Error message\n");
}

TEST(LoggerTest, ShouldLogInfoWarningAndError)
{
  auto logger = TestLogger<LogLevel::INFO>();

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.out, "[INFO] Info message\n");
  EXPECT_EQ(logger.err, "[WARNING] Warning message\n[ERROR] Error message\n");
}

TEST(LoggerTest, ShouldLogDebugInfoWarningAndError)
{
  auto logger = TestLogger<LogLevel::DEBUG>();

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.out, "[DEBUG] Debug message\n[INFO] Info message\n");
  EXPECT_EQ(logger.err, "[WARNING] Warning message\n[ERROR] Error message\n");
}

TEST(LoggerTest, ShouldLogWithPreamble)
{
  auto logger = TestLogger<LogLevel::DEBUG>("TestPreamble");

  logger.debug("Debug message");
  logger.info("Info message");
  logger.warning("Warning message");
  logger.error("Error message");

  EXPECT_EQ(logger.out, "[TestPreamble][DEBUG] Debug message\n[TestPreamble][INFO] Info message\n");
  EXPECT_EQ(logger.err, "[TestPreamble][WARNING] Warning message\n[TestPreamble][ERROR] Error message\n");
}

