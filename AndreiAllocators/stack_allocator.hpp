#ifndef STACK_ALLOCATOR
#define STACK_ALLOCATOR

#include <cstddef>

template <std::size_t Size>
class stack_allocator {
  void* allocate(std::size_t size) {
    auto nr = round_to_aligned(size);
    if (nr > (data_ + Size) - position_) {
      return nullptr;
    }

    void* result = position_;
    position_ += nr;
    return result;
  }

  void deallocate(void* ptr) {}

  bool owns(void* ptr) { return data_ <= ptr && ptr < data_ + Size; }

  char data_[Size];
  char* position_;
};

#endif  // !STACK_ALLOCATOR
