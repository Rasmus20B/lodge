#pragma once

#include <atomic>
#include <iostream>

namespace lodge {

struct Queue {
  explicit Queue(char *buf, std::size_t size)
      : m_writeIndex(0), m_readIndex(0), m_dataEnd(0), m_size(size),
        m_buf(buf) {}

  std::atomic<std::size_t> m_writeIndex;
  std::atomic<std::size_t> m_readIndex;
  std::size_t m_dataEnd;
  std::size_t m_size;
  char *m_buf;
};

} // namespace lodge
