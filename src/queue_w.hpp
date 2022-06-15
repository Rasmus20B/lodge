#pragma once

#include "queue.hpp"

namespace lodge {
class Queue_w {
  explicit Queue_w(Queue &q_) : q(&q_){};

public:
private:
  Queue *q;
  char *buf() { return q->m_buf; }
};
} // namespace lodge
