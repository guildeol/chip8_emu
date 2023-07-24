#include <iostream>
#include <fmt/format.h>
#include <fmt/color.h>
#include <sstream>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "logger/base_logger.h"
#include "logger/console_logger.h"

using namespace testing;
using namespace Logger;

TEST(LoggerTest, ShouldLogNothing)
{
  std::stringstream logStream;

  BaseLogger log = BaseLogger(LogLevel::OFF, &logStream, &logStream);

  log.error("Test!");
  log.warning("Test!");
  log.info("Test!");
  log.debug("Test!");
  EXPECT_EQ(logStream.str(), "");
}

TEST(LoggerTest, ShouldLogError)
{
  std::stringstream logStream;
  std::stringstream expectedMsg;

  BaseLogger log = BaseLogger(LogLevel::ERROR, &logStream, &logStream);

  expectedMsg << fmt::format(fg(fmt::color::red), "[ERR]: Test!") << std::endl;

  log.error("Test!");
  EXPECT_EQ(logStream.str(), expectedMsg.str());
}

TEST(LoggerTest, ShouldLogWarning)
{
  std::stringstream logStream;
  std::stringstream expectedMsg;

  BaseLogger log = BaseLogger(LogLevel::WARNING, &logStream, &logStream);

  expectedMsg << fmt::format(fg(fmt::color::yellow), "[WRN]: Test!") << std::endl;

  log.warning("Test!");
  EXPECT_EQ(logStream.str(), expectedMsg.str());
}

TEST(LoggerTest, ShouldLogInfo)
{
  std::stringstream logStream;
  std::stringstream expectedMsg;

  BaseLogger log = BaseLogger(LogLevel::INFO, &logStream, &logStream);

  expectedMsg << fmt::format(fg(fmt::color::green), "[INF]: Test!") << std::endl;

  log.info("Test!");
  EXPECT_EQ(logStream.str(), expectedMsg.str());
}

TEST(LoggerTest, ShouldLogDebug)
{
  std::stringstream logStream;
  std::stringstream expectedMsg;

  BaseLogger log = BaseLogger(LogLevel::DEBUG, &logStream, &logStream);

  expectedMsg << fmt::format(fg(fmt::color::gray), "[DBG]: Test!") << std::endl;

  log.debug("Test!");
  EXPECT_EQ(logStream.str(), expectedMsg.str());
}
