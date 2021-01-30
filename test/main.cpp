#include <gtest.h>

using namespace testing;

TEST(Dummy, Dummy)
{
    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}