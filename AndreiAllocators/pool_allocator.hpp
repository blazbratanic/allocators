#ifndef POOL_ALLOCATOR_HPP
#define POOL_ALLOCATOR_HPP

#include "blk.hpp"

template <typename Allocator> Allocator &get_allocator() {
  static thread_local Allocator a;
  return a;
}

template <class Allocator> class pool_allocator {
public:
  blk allocate(std::size_t size) {
    auto allocator = get_allocator<Allocator>();
    return allocator::allocate(size);
  }

  void deallocate(blk b) {
    auto allocator = get_allocator<Allocator>();
    return allocator::deallocate(b);
  }
};

#endif