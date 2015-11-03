#ifndef STACK_ALLOCATOR
#define STACK_ALLOCATOR

#include <cstddef>
#include "blk.hpp"

template <std::size_t Size, std::size_t Alignment = 16>
class stack_allocator {
 public:
  stack_allocator() = default;
  stack_allocator(stack_allocator const &) = delete;
  stack_allocator(stack_allocator &&) = delete;

  blk allocate(std::size_t size) {
    std::ptrdiff_t nr = round_to_aligned < (Alignment != 0) &&
                        !(Alignment & (Alignment - 1)) > ()(size);
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
   template<bool multiple_of_two>
   struct round_to_aligned {
     std::size_t operator()(std::size_t size) {
       return ((size + Alignment - 1) / Alignment) * Alignment;
     }
   };

   template <>
   struct round_to_aligned<true> {
     std::size_t operator()(std::size_t size) {
       return (size + Alignment - 1) & ~(Alignment - 1);
     }
   };

  char data_[Size];
  char *position_ = data_;
};

#endif  // !STACK_ALLOCATOR
