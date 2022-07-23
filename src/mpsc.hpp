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
    struct alignas(nodeSize) Mpsc {
public:
  Mpsc() noexcept = default;

  [[nodiscard]] bool empty() const noexcept {
    return m_head.load(std::memory_order_relaxed) == m_tail;
  }

  [[nodiscard]] bool full() const noexcept {
    // return (m_head.load(std::memory_order_relaxed) + nodeSize) == m_tail;
    return (m_head.load(std::memory_order_relaxed) == m_totalNodes);
  }

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
}; // namespace lodge
