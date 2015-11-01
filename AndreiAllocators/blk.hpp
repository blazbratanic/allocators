#ifndef BLK_HPP
#define BLK_HPP

#include <cstddef>

struct blk {
  void* ptr;
  std::size_t length;
};

#endif