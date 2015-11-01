#ifndef SEGREGATOR_HPP
#define SEGREGATOR_HPP

#include <cstddef>

#include "blk.hpp"

template <std::size_t threshold, class SmallAllocator, class LargeAllocator>
class segregator : private SmallAllocator, private LargeAllocator {
  blk allocate(std::size_t size) {
    if (size < threshold) {
      return SmallAllocator::allocate(size);
    }
    return LargeAllocator::allocate(size);
  }

  void deallocate(blk b) {
    if (b.length < threshold) {
      SmallAllocator::deallocate(b);
    } else {
      LargeAllocator::deallocate(b);
    }
  }

  bool owns(blk b) {
    if (b.length < threshold) {
      return SmallAllocator::owns(b);
    } else {
      return LargeAllocator::owns(b);
    }
  }
};

#endif