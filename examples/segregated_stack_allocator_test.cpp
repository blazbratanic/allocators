#include "segregated_freelist_allocator.hpp"
#include "stack_allocator.hpp"

#include "bucket_allocator.hpp"

#include "gtest/gtest.h"

TEST(SegregatedStackAllocator, Allocation) {
  segregated_freelist_allocator<stack_allocator<16 * 1024, 16>, 16, 32, 16, 512> allocator;

  for (int i = 16; i <= 32; ++i) {
    ASSERT_TRUE(allocator.allocate(i)); 
  }
}

template <std::size_t Size>
using SFA = segregated_freelist_allocator<stack_allocator<32 * 2048>, 16, Size>;

TEST(BucketizedSegregatedStackAllocator, Allocation) {
  log_bucket_allocator<SFA, 16, 1024> allocator;

  for (int i = 16; i <= 1024; ++i) {
    auto b = allocator.allocate(i);
    ASSERT_TRUE(b);
    allocator.deallocate(b);
  }
}