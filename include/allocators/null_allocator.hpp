#ifndef NULL_ALLOCATOR
#define NULL_ALLOCATOR

#include <cstddef>
#include <cassert>

#include "blk.hpp"

class null_allocator {
 public:
  null_allocator() = default;
  null_allocator(null_allocator const &) = delete;
  null_allocator(null_allocator &&) = delete;

  blk allocate(std::size_t size) { return {nullptr, 0}; }

  void deallocate(blk b) { assert(b.ptr == nullptr); }

  bool owns(blk b) { return b.ptr == nullptr; }
};
#endif  // !NULL_ALLOCATOR
