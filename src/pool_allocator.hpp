#ifndef POOL_ALLOCATOR_HPP
#define POOL_ALLOCATOR_HPP

#include "blk.hpp"

#ifndef thread_local
#define thread_local __declspec(thread)
#endif

template <typename Allocator> Allocator &get_allocator() {
  static Allocator a;
  return a;
}

template <class Allocator> class pool_allocator {
public:
  blk allocate(std::size_t size) {
    auto& allocator = get_allocator<Allocator>();
    return allocator.allocate(size);
  }

  void deallocate(blk b) {
    auto& allocator = get_allocator<Allocator>();
    return allocator.deallocate(b);
  }
};

#endif