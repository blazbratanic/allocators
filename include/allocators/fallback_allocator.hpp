#ifndef FALLBACK_ALLOCATOR
#define FALLBACK_ALLOCATOR

#include <cstddef>

#include "blk.hpp"

template <class Primary, class Fallback>
class fallback_allocator : private Primary, private Fallback {
 public:
  fallback_allocator() = default;
  fallback_allocator(fallback_allocator const &) = delete;
  fallback_allocator(fallback_allocator &&) = delete;

  blk allocate(std::size_t size) {
    blk result = Primary::alocate(size);
    if (!result.ptr) {
      result = Fallback::allocate(size);
    }
    return result;
  }

  void deallocate(blk b) {
    if (Primary::owns(b)) {
      Primary::deallocate(b);
    } else {
      Fallback::deallocate(b);
    }
  }

  bool owns(blk b) { return Primary::owns(b) || Fallback::owns(b); }
};

#endif
