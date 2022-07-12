

#include "gtest/gtest.h"

#include <limits>
#include <optional>

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

  EXPECT_EQ(2048, count);
}

TEST(QueueTest, push_full_fail) {
  lodge::lQueue<short, 32> q;

  short x = 0;
  short count = 1;
  while (count < 2048) {
    count++;
    q.push(x);
  }

  EXPECT_EQ(false, q.push(x));
}

TEST(QueueTest, pop_success) {
  lodge::lQueue<int, 32> q;
  auto x = 54;
  auto y = 9;
  auto z = 231;
  q.push(x);
  q.push(y);
  q.push(z);

  EXPECT_EQ(54, q.pop());
  EXPECT_EQ(9, q.pop());
  EXPECT_EQ(231, q.pop());

  EXPECT_EQ(true, q.empty());
}

TEST(QueueTest, pop_empty_fail) {
  lodge::lQueue<long, 32> q;
  EXPECT_EQ(std::nullopt, q.pop());
}
