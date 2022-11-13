#include "gtest/gtest.h"
#include <limits>
#include <array>
#include <optional>

#include "../src/log_item.h"
#include "../src/queue.h"
#include <experimental/source_location>

TEST(QueueMCTest, 5threads) { 

  int count = 0;
  while( count < 10) {
    lodge::lQueue<int, 32> q; 
    std::thread a([&] { q.push(1); }); 
    std::thread b([&] { q.push(2); });
    std::thread c([&] { q.push(3); });
    std::thread d([&] { q.push(4); });
    std::thread e([&] { q.push(5); });
    std::thread f([&] { q.push(6); });
    std::thread g([&] { q.push(7); });
    std::thread h([&] { q.push(8); });
    std::thread i([&] { q.push(9); });
    std::thread j([&] { q.push(10); });
    a.join();
    b.join();
    c.join();
    d.join();
    e.join();
    f.join();
    g.join();
    h.join();
    i.join();
    j.join();

    std::array<int, 10> r{};

    for(int i = 0; i < 10; i++) {
      r[i] = q.try_pop().value();
    }

    std::sort(r.begin(), r.end());
    for(int i = 0; i < 10; i++) {
      EXPECT_EQ(i + 1, r[i]);
    }
    count++;
  }
}
