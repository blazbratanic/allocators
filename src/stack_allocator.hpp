#ifndef STACK_ALLOCATOR
#define STACK_ALLOCATOR

#include <cstddef>
#include "blk.hpp"

template <std::size_t Size>
class stack_allocator {
 public:
  blk allocate(std::size_t size) {
    auto nr = round_to_aligned(size);
    if (nr > (data_ + Size) - position_) {
      return {nullptr, 0};
    }

    blk result = {position_, size};
    position_ += nr;
    return result;
  }

  void deallocate(blk b) {
    if (b.ptr + b.length == position_) {
      position_ = b.ptr;
    }
  }

  bool owns(blk b) { return data_ <= b.ptr && b.ptr < data_ + Size; }

 private:
  char data_[Size];
  char* position_;
};

#endif  // !STACK_ALLOCATOR
