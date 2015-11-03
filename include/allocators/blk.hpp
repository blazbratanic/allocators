#ifndef BLK_HPP
#define BLK_HPP

#include <cstddef>

struct blk {
  void* ptr;
  std::size_t length;

  operator bool() { return ptr; }

  void reset() {
    ptr = nullptr;
    length = 0;
  }
};

#endif