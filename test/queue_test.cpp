

#include "gtest/gtest.h"
#include <limits>
#include <optional>

#include "../src/log_item.hpp"
#include "../src/queue.hpp"
#include <experimental/source_location>

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

  EXPECT_EQ(54, q.try_pop());
  EXPECT_EQ(9, q.try_pop());
  EXPECT_EQ(231, q.try_pop());

  EXPECT_EQ(true, q.empty());
}

TEST(QueueTest, pop_empty_fail) {
  lodge::lQueue<long, 32> q;
  EXPECT_EQ(std::nullopt, q.try_pop());
}

TEST(QueueTest, push_pop_string) {
  lodge::lQueue<std::string, 64> q;
  q.push(std::move("this is not a small string\n"));
  q.push(std::move("Neither is this one\n"));
  q.push(std::move("Nor this one is\n"));
  q.push(std::move("we are not working with small strings\n"));

  std::optional<std::string> a = q.try_pop();
  EXPECT_EQ("this is not a small string\n", a.value());
  EXPECT_EQ("Neither is this one\n", q.try_pop());
  EXPECT_EQ("Nor this one is\n", q.try_pop());
  EXPECT_EQ("we are not working with small strings\n", q.try_pop());
}

TEST(QueueTest, push_pop_log_item) {
  lodge::lQueue<lodge::LogItem, 128> lq;
  std::string buf =
      "This is a test of logitem, not sure about the size though\n";
  lodge::Level l = lodge::default_log_level;
  std::experimental::source_location loc{};
  lodge::LogItem i(loc, l, buf);

  lq.push(i);
  lq.push(i);
  lq.push(i);
  lq.push(i);

  std::optional<lodge::LogItem> r = lq.try_pop();
  EXPECT_EQ(i, r.value());
  std::cout << r->buf;
  EXPECT_EQ(i, lq.try_pop().value());
  EXPECT_EQ(i, lq.try_pop().value());
  EXPECT_EQ(i, lq.try_pop().value());
}
