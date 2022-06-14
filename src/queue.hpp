#pragma once

#include <atomic>
#include <iostream>

namespace lodge {

class Queue {
  explicit Queue(char *buf, std::size_t size) {}

private:
  std::atomic<std::size_t> writeIndex;
  std::atomic<std::size_t> readIndex;
};

} // namespace lodge
