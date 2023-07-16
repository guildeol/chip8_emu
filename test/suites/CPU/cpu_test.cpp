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
  CpuMemory memory;
  Cpu chip8(memory);

  vector<char> testFileContents = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  auto result = chip8.loadGame("/tmp/chip8_test.ch8");
  EXPECT_EQ(result, CHIP8_SUCCESS);
  EXPECT_EQ(memcmp(memory.workRam, testFileContents.data(), testFileContents.size()), 0);
}

TEST(CpuTest, ShouldReturnErrorIfFileDoesNotExist)
{
  CpuMemory memory;
  Cpu chip8(memory);

  auto result = chip8.loadGame("invalidFileName");
  EXPECT_EQ(result, CHIP8_ERROR_LOADING);
}
