#ifndef FREELIST_ALLOCATOR
#define FREELIST_ALLOCATOR

#include <cstddef>
#include "blk.hpp"

template <class Allocator, std::size_t AllocationBlockCount = 16,
          std::size_t MaxSize = 1024>
class segregated_freelist_allocator : private Allocator{
 public:
  blk allocate(std::size_t size) {
    if (end == nullptr) {
      blk b = Allocator::allocate(size * AllocationBlockCount);
      segregate(b.ptr);
    }


  }

  std::size_t good_size(std::size_t size) const {
    return Allocator::good_size(size);
  }

  void deallocate(blk b) {}

  bool owns(blk b) {}

 private:
  void segregate(void* ptr) {

  
  }

  void* end;
};

#endif