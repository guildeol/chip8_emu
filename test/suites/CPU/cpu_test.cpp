#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "cpu.h"

using namespace std;
using namespace testing;

bool isClear = false;
void testClearCallback()
{
  isClear = true;
}

constexpr int testDisplayWidth = 64;
constexpr int testDisplayHeight = 32;
std::vector<bool> testPixels(testDisplayWidth * testDisplayHeight);
bool testDrawCallback(int x_coord, int y_coord)
{
  auto p = x_coord + (y_coord * testDisplayWidth);
  bool wasOn = false;

  if (testPixels[p] == true)
    wasOn = true;

  testPixels[p] = testPixels[p] ^ true;

  return wasOn;
}

void run(Cpu &cpu)
{
  cpu.fetch();
  cpu.decode();
  cpu.execute();
}

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

class CpuTest : public Test
{
  public:
    CpuTest()
    {
      isClear = false;
      std::fill(begin(testPixels), end(testPixels), false);
    }
};

TEST_F(CpuTest, ShouldLoadGameFile)
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

TEST_F(CpuTest, ShouldReturnErrorIfFileDoesNotExist)
{
  Cpu chip8;

  auto result = chip8.loadGame("invalidFileName");
  EXPECT_EQ(result, CHIP8_ERROR_LOADING);
}

TEST_F(CpuTest, ShouldFetch)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x00, 0xE0};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  EXPECT_EQ(chip8.currentInstruction, 0x00E0);
}

TEST_F(CpuTest, ShouldFetchMultiple)
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

TEST_F(CpuTest, ShouldNotFetchBeyondLimit)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x00, 0xE0};

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  EXPECT_EQ(chip8.currentInstruction, 0x00E0);

  EXPECT_THROW(chip8.fetch(), CpuException);
}

TEST_F(CpuTest, ShouldDecodeInstruction)
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

TEST_F(CpuTest, ShouldExecuteCLS)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x00, 0xE0};
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.setClearCallback(testClearCallback);

  chip8.fetch();
  chip8.decode();
  chip8.execute();

  EXPECT_TRUE(isClear);
}

TEST_F(CpuTest, ShouldExecuteLDINNN)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0xA2, 0x50};
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  chip8.decode();
  chip8.execute();

  EXPECT_EQ(chip8.I, 0x250);
}

TEST_F(CpuTest, ShouldExecuteLDVXNN)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x60, 0x55};
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  chip8.decode();
  chip8.execute();

  EXPECT_EQ(chip8.V[0], 0x55);
}

TEST_F(CpuTest, ShouldExecuteJPNNN)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {0x12, 0x00};
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  try
  {
    chip8.fetch();
    chip8.decode();
    chip8.execute();

    chip8.fetch();
    chip8.decode();
    chip8.execute();
  }
  catch(const std::exception& e)
  {
    FAIL();
  }
}

TEST_F(CpuTest, ShouldExecuteADDVXNN)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {
    0x73, 0x20, // ADD V3, 0x20
    0x73, 0x30  // ADD V3, 0x30
  };
  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);

  chip8.loadGame("/tmp/chip8_test.ch8");

  chip8.fetch();
  chip8.decode();
  chip8.execute();

  chip8.fetch();
  chip8.decode();
  chip8.execute();

  EXPECT_EQ(chip8.V[3], 0x50);
}

TEST_F(CpuTest, ShouldExecuteDRWXYN)
{
  Cpu chip8;
  vector<uint8_t> testFileContents = {
    0xA2, 0x08, // 0x200: LD I, 0x208
    0x60, 0x00, // 0x202: LD V0, 0x00
    0x61, 0x00, // 0x204: LD V1, 0x00
    0xD0, 0x01, // 0x206: DRW V0, V1 0x1
    0xFF, 0xFF, // 0x208: Draw data: 0xFFFF
  };

  chip8.setDrawCallback(testDrawCallback);

  Chip8TestFile testFile = Chip8TestFile("/tmp/chip8_test.ch8", testFileContents);
  chip8.loadGame("/tmp/chip8_test.ch8");

  run(chip8);
  run(chip8);
  run(chip8);
  run(chip8);

  auto expectedPixels = std::vector<bool>(8);
  std::fill(begin(expectedPixels), end(expectedPixels), true);

  EXPECT_TRUE(std::equal(begin(testPixels), begin(testPixels) + expectedPixels.size(), begin(expectedPixels)));
}
