#ifndef FREELIST_ALLOCATOR
#define FREELIST_ALLOCATOR

#include <cstddef>
#include <cassert>

#include "blk.hpp"

namespace detail {
void*& nextof(void* ptr) { return *static_cast<void**>(ptr); }
}

template <class Allocator, std::size_t MinSize, std::size_t MaxSize,
          std::size_t AllocationBlockCount = 16, std::size_t PoolMaxSize = 1024>
class segregated_freelist_allocator : private Allocator {
  static_assert(MaxSize >= sizeof(void*),
                "Maximum size must be able to hold a pointer!");

 public:
  static const std::size_t min_size = MinSize;
  static const std::size_t max_size = MaxSize;
  static const std::size_t allocation_block_count = AllocationBlockCount;
  static const std::size_t pool_max_size = PoolMaxSize;

  segregated_freelist_allocator() = default;
  segregated_freelist_allocator(segregated_freelist_allocator const&) = delete;
  segregated_freelist_allocator(segregated_freelist_allocator&&) = delete;

  blk allocate(std::size_t size) {
    assert(MinSize <= size && size <= MaxSize && "Invalid Size");

    if (end_ == nullptr) {
      if (size_ + AllocationBlockCount > PoolMaxSize) {
        return {nullptr, 0};
      }

      blk b = Allocator::allocate(MaxSize * AllocationBlockCount);
      if (!b) return {nullptr, 0};

      segregate(static_cast<char*>(b.ptr));
      size_ += AllocationBlockCount;
    }

    void* result = end_;
    end_ = detail::nextof(end_);

    return {result, MaxSize};
  }

  void deallocate(blk b) {
    detail::nextof(b.ptr) = end_;
    end_ = b.ptr;
  }

  bool owns(blk b) const { return MinSize <= b.length && b.length <= MaxSize; }

  std::size_t good_size(std::size_t size) const { return MaxSize; }

 private:
  void segregate(char* ptr) {
    for (int i = 0; i < AllocationBlockCount; ++i) {
      detail::nextof(ptr + i * MaxSize) = end_;
      end_ = ptr + i * MaxSize;
    }
  }

  void* end_ = nullptr;
  std::size_t size_ = 0u;
};

#endif