#ifndef BLK_HPP
#define BLK_HPP

#include <cstddef>

struct blk {
  void* ptr;
  std::size_t length;

  operator bool() const { return ptr != nullptr; }

  void reset() {
    ptr = nullptr;
    length = 0;
  }
};

#endif