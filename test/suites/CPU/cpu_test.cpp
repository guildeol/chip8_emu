#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "cpu.h"

using namespace std;
using namespace testing;

class Chip8TestFile
{
  public:
    Chip8TestFile(string filename, vector<char> &contents)
    {
      ofstream testFile(filename);

      testFile.write(contents.data(), contents.size());

      testFile.close();
    }
};

TEST(CpuTest, ShouldLoadGameFile)
{
  CpuMemory *memory_p = new CpuMemory();
  Cpu chip8(memory_p);

  vector<char> testFileContents = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  auto result = chip8.loadGame("/tmp/chip8_test.ch8");
  EXPECT_EQ(result, CHIP8_SUCCESS);
  EXPECT_EQ(memcmp(memory_p->workRam.start, testFileContents.data(), testFileContents.size()), 0);
  EXPECT_EQ(memory_p->workRam.size, testFileContents.size());
}

TEST(CpuTest, ShouldReturnErrorIfFileDoesNotExist)
{
  Cpu chip8;

  auto result = chip8.loadGame("invalidFileName");
  EXPECT_EQ(result, CHIP8_ERROR_LOADING);
}

TEST(CpuTest, ShouldFetch)
{
  Cpu chip8;
  vector<char> testFileContents = {0x00, 0x0E};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  auto instruction = chip8.fetch();
  EXPECT_EQ(instruction, 0x0E00);
}

TEST(CpuTest, ShouldFetchMultiple)
{
  Cpu chip8;
  vector<char> testFileContents = {0x00, 0x0E, 0x34, 0x12};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  auto instruction = chip8.fetch();
  EXPECT_EQ(instruction, 0x0E00);

  instruction = chip8.fetch();
  EXPECT_EQ(instruction, 0x1234);
}

TEST(CpuTest, ShouldNotFetchBeyondLimit)
{
  Cpu chip8;
  vector<char> testFileContents = {0x00, 0x0E};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  auto instruction = chip8.fetch();
  EXPECT_EQ(instruction, 0x0E00);

  EXPECT_THROW(chip8.fetch(), CpuException);
}
