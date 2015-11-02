#ifndef FREELIST_ALLOCATOR
#define FREELIST_ALLOCATOR

#include <cstddef>

#include "blk.hpp"

class freelist_allocator {
 public:
  blk allocate(std::size_t size) {}

  void deallocate(blk b) {}

  bool owns(blk b) {}
};

#endif