#include "gtest/gtest.h"

#include <limits>
#include <optional>

#include "../src/queue.hpp"

TEST(concurrentQueueTest, pushTest) {
  lodge::lQueue<int, 32> q;
  std::thread a([&] { q.push(1); });
  std::thread b([&] { q.push(2); });
  std::thread c([&] { q.push(3); });
  std::thread d([&] { q.push(4); });
  std::thread e([&] { q.push(5); });
  // std::jthread b = std::jthread(&lodge::lQueue<int, 32>::push, q, 2);
  // std::jthread c = std::jthread(&lodge::lQueue<int, 32>::push, q, 3);
  // std::jthread d = std::jthread(&lodge::lQueue<int, 32>::push, q, 4);
  // std::jthread e = std::jthread(&lodge::lQueue<int, 32>::push, q, 5);
  a.join();
  b.join();
  c.join();
  d.join();
  e.join();

  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(q.try_pop(), i);
  }
}
