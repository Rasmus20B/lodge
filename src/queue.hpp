#pragma once

#include <array>
#include <atomic>
#include <bit>
#include <iostream>
#include <optional>
#include <thread>

#include "levels.hpp"
#include "log_item.hpp"

namespace lodge {

// Queue of fixed size (power of 2) nodes
template <typename T, const std::size_t nodeSize>
requires(std::has_single_bit(nodeSize), nodeSize < 65536)
    // Alignas to stop potential false sharing between threads
    struct alignas(nodeSize) lQueue {
public:
  lQueue() noexcept = default;

  [[nodiscard]] bool empty() noexcept {
    return m_head.load(std::memory_order_relaxed) == m_tail;
  }

  [[nodiscard]] bool full() noexcept {
    // return (m_head.load(std::memory_order_relaxed) + nodeSize) == m_tail;
    return (m_head.load(std::memory_order_relaxed) == m_totalNodes);
  }

  bool push(T val) noexcept {

    uint16_t currentHead;
    //  write something, increment the head, then increment the last readable
    do {

      currentHead = m_head.load();
      //  Check if the Queue is currently full
      [[unlikely]] if (full()) return false;
    }
    // exchange the private write index with the current thread's write index
    while (!m_head.compare_exchange_strong(currentHead, (currentHead + 1)));
    nodes[m_head.load() - 1] = val;

    // maxRead needs to catch up now that valid data is read to be read
    while (!m_maxRead.compare_exchange_strong(currentHead, (currentHead + 1))) {
      std::this_thread::yield();
    };

    return true;
  }

  [[nodiscard]] std::optional<T> try_pop() noexcept {

    [[unlikely]] if (m_head == m_tail) { return std::nullopt; }

    std::optional<T> data = nodes[m_tail];

    m_tail++;
    return data;
  }

  // T pop() noexcept {
  //   auto data = nodes[m_tail];

  //   m_tail++;
  //   return data;
  // }

  // template <typename V>
  // requires std::is_same<V, lodge::log_item>::value static void print() {

  //   for (auto &i : nodes) {
  //     std::cout << i.time.time_since_epoch() << " : " <<
  //     to_string_view(i.level)
  //               << " " << i.buf.data() << "\n";
  //   }
  //   return;
  // }

  // static void print() noexcept {

  //   for (uint16_t i = m_tail; i <= m_head; i++) {
  //     std::cout << nodes.at(i) << '\n';
  //   }
  // }

  std::size_t getSize() { return m_size; }
  std::size_t getNodeSize() { return m_nodeSize; }
  std::size_t getTotalNodes() { return m_totalNodes; }

private:
  constexpr static std::size_t m_size = 65535;
  constexpr static std::size_t m_nodeSize = nodeSize;
  constexpr static std::size_t m_totalNodes = m_size / m_nodeSize;
  std::array<T, m_totalNodes> nodes;
  std::atomic<uint16_t> m_head = 0;
  std::atomic<uint16_t> m_maxRead = 0;
  // static inline std::atomic<uint16_t> m_tail = 0;
  uint16_t m_tail = 0;
};

} // namespace lodge
