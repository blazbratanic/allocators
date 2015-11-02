#ifndef MALLOC_ALLOCATOR
#define MALLOC_ALLOCATOR

#include <cstddef>
#include <cstdlib>

#include "blk.hpp"

class malloc_allocator {
 public:
  blk allocate(std::size_t size) { return {malloc(size), size}; }

  void deallocate(blk b) { free(b.ptr); }

  bool owns(blk ptr) { return true; }
};

#endif  // !MALLOC_ALLOCATOR
