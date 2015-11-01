#ifndef NULL_ALLOCATOR
#define NULL_ALLOCATOR

#include <cstddef>
#include <cassert>

#include "blk.hpp"

class null_allocator {
 public:
  blk allocate(std::size_t size) { return {nullptr, 0}; }

  void deallocate(blk b) { assert(b.ptr == nullptr); }

  bool owns(blk b) { return b.ptr == nullptr; }
};
#endif  // !NULL_ALLOCATOR
