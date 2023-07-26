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
    Chip8TestFile(string filename, vector<uint8_t> &contents)
    {
      ofstream testFile(filename);

      testFile.write(reinterpret_cast<char *>(contents.data()), contents.size());

      testFile.close();
    }
};

TEST(CpuTest, ShouldLoadGameFile)
{
  CpuMemory *memory_p = new CpuMemory();
  Cpu chip8(memory_p);

  vector<uint8_t> testFileContents = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
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
  vector<uint8_t> testFileContents = {0x00, 0xE0};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  EXPECT_EQ(chip8.currentInstruction, 0x00E0);
}

TEST(CpuTest, ShouldFetchMultiple)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x00, 0xE0, 0x12, 0x34};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  EXPECT_EQ(chip8.currentInstruction, 0x00E0);

  chip8.fetch();
  EXPECT_EQ(chip8.currentInstruction, 0x1234);
}

TEST(CpuTest, ShouldNotFetchBeyondLimit)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x00, 0xE0};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  EXPECT_EQ(chip8.currentInstruction, 0x00E0);

  EXPECT_THROW(chip8.fetch(), CpuException);
}

TEST(CpuTest, ShouldDecodeInstruction)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x12, 0x34};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  chip8.decode();

  EXPECT_EQ(chip8.decodedInstruction.fields[0].byte, 0x12);
  EXPECT_EQ(chip8.decodedInstruction.fields[0].nibble.high, 0x01);
  EXPECT_EQ(chip8.decodedInstruction.fields[0].nibble.low, 0x02);

  EXPECT_EQ(chip8.decodedInstruction.fields[1].byte, 0x34);
  EXPECT_EQ(chip8.decodedInstruction.fields[1].nibble.high, 0x03);
  EXPECT_EQ(chip8.decodedInstruction.fields[1].nibble.low, 0x04);
}
