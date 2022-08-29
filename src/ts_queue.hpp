#include <deque>
#include <mutex>
#include <condition_variable> 

template<typename T>
class Ts_queue {
  public:
    Ts_queue() = default;
    Ts_queue(const Ts_queue<T>&) = delete;

    const T& front() {
      std::scoped_lock lock(muxQueue);
      return dequeue.front();
    }

    const T& back() {
      std::scoped_lock lock(muxQueue);
      return dequeue.back();
    }

    T pop_front() {
      std::scoped_lock lock(muxQueue);
      auto t = std::move(dequeue.front());
      dequeue.pop_front();
      return t;
    }
    T pop_back() {
      std::scoped_lock lock(muxQueue);
      auto t = std::move(dequeue.front());
      dequeue.pop_back();
      return t;
    }
    void push_back(const T& item) {
      std::scoped_lock lock(muxQueue);
      dequeue.emplace_back(std::move(item));
      std::unique_lock<std::mutex> ul(muxBlocking);
      cvBlocking.notify_one();
    }

    void push_front(const T& item) {
      std::scoped_lock lock(muxQueue);
      dequeue.emplace_front(std::move(item));
      std::unique_lock<std::mutex> ul(muxBlocking);
      cvBlocking.notify_one();
    }

    bool empty() {
      std::scoped_lock lock(muxQueue);
      return dequeue.empty();
    }

    void clear() {
      std::scoped_lock lock(muxQueue);
      dequeue.clear();
    }

    void wait() {
      while(empty()) {
        std::unique_lock<std::mutex> ul(muxBlocking);
        cvBlocking.wait(ul);
      }
    }

  protected: 
    std::mutex muxQueue;
    std::mutex muxBlocking;
    std::deque<T> dequeue;
    std::condition_variable cvBlocking;
};
