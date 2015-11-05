#ifndef CASCADING_ALLOCATOR_HPP
#define CASCADING_ALLOCATOR_HPP

#include <list>

#include "blk.hpp"

template <class Allocator>
class cascading_allocator {

  blk allocate(std::size_t size) {
    if (allocators.empty() || !(auto b = allocators.back().allocate(size))) {
      allocators.emplace_back();
    }
    return allocators.back().allocate(size);
  }

  void deallocate(blk b) {
    allocators.back().deallocate(b);
  }

  bool owns(blk b) {
    for (auto const & e: allocators) {
      if (e.owns(b)) return true;
    }
    return false;
  }


private:
  std::list<Allocator> allocators;

};


#endif