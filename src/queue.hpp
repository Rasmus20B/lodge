#pragma once

#include <array>
#include <atomic>
#include <bit>
#include <iostream>
#include <thread>

namespace lodge {

// Queue of fixed size (power of 2) nodes
template <typename T, const std::size_t nodeSize>
requires(std::has_single_bit(nodeSize), nodeSize < 65536)
    // Alignas to stop potential false sharing between threads
    struct alignas(nodeSize) lQueue {
public:
  lQueue() noexcept = default;

  [[nodiscard]] static inline bool empty() noexcept {
    return m_head.load(std::memory_order_relaxed) == m_tail;
  }

  [[nodiscard]] static inline bool full() noexcept {
    // return (m_head.load(std::memory_order_relaxed) + nodeSize) == m_tail;
    return (m_head.load(std::memory_order_relaxed) == m_totalNodes);
  }

  static bool push(T &val) {

    uint16_t currentHead;
    // uint16_t currentTail;
    //  write something, increment the head, then increment the last readable
    do {

      currentHead = m_head.load();
      // currentTail = m_tail;
      //  Check if the Queue is currently full
      [[unlikely]] if (full()) return false;
    }
    // exchange the private write index with the current thread's write index
    while (!m_head.compare_exchange_strong(currentHead, (currentHead + 1)));
    nodes[m_head.load()] = val;

    // maxRead needs to catch up now that valid data is read to be read
    while (!m_maxRead.compare_exchange_strong(currentHead, (currentHead + 1))) {
      std::this_thread::yield();
    };

    return true;
  }

  static T pop() { return nodes[m_maxRead]; }

  static inline std::size_t getSize() { return m_size; }
  static inline std::size_t getNodeSize() { return m_nodeSize; }
  static inline std::size_t getTotalNodes() { return m_totalNodes; }

private:
  static constexpr std::size_t m_size = 65535;
  static constexpr std::size_t m_nodeSize = nodeSize;
  static constexpr std::size_t m_totalNodes = m_size / m_nodeSize;
  static inline std::array<T, m_totalNodes> nodes{};
  static inline std::atomic<uint16_t> m_head = 0;
  static inline std::atomic<uint16_t> m_maxRead = 0;
  static inline uint16_t m_tail = 0;
};

} // namespace lodge
