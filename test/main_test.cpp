#include "gtest/gtest.h"

#include "../src/lodge.hpp"

TEST(LogTest, format) { EXPECT_EQ(0, lodge::debug("Hello {}", "World")); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
