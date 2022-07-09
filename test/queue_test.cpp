

#include "gtest/gtest.h"

#include <limits>

#include "../src/queue.hpp"
TEST(QueueTest, empty) {
  lodge::lQueue<int, 32> q;
  EXPECT_EQ(true, q.empty());
}

TEST(QueueTest, full_false) {
  lodge::lQueue<short, 32> q;

  EXPECT_EQ(false, q.full());
}

TEST(QueueTest, full_true) {
  lodge::lQueue<short, 32> q;

  short x = 0;
  short count = 1;
  while (!q.full()) {
    count++;
    q.push(x);
  }

  std::cout << count << '\n';
  EXPECT_EQ(2048, count);
}

TEST(QueueTest, push_fail) {
  lodge::lQueue<short, 32> q;

  short x = 0;
  short count = 1;
  while (count < 2048) {
    count++;
    q.push(x);
  }

  EXPECT_EQ(false, q.push(x));
}
