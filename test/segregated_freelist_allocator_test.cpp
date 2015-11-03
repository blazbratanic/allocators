#include "gtest/gtest.h"
#include "segregated_freelist_allocator.hpp"
#include "malloc_allocator.hpp"

TEST(SegregatedFreelist, Allocation) {
  segregated_freelist_allocator<malloc_allocator, 16, 32, 16, 1024> allocator;

  for (int i = 16; i <= 32; ++i) {
    ASSERT_TRUE(allocator.allocate(i)); 
  }
}

TEST(SegregatedFreelist, Deallocation) {
  segregated_freelist_allocator<malloc_allocator, 16, 32, 16, 1024> allocator;

  for (int i = 0; i < 2048; ++i) {
    auto b = allocator.allocate(32);
    ASSERT_TRUE(b);
    allocator.deallocate(b);
  }
}

TEST(SegregatedFreelist, MaxSize) {
  segregated_freelist_allocator<malloc_allocator, 16, 32, 16, 1024> allocator;

  for (int i = 0; i < 1024; ++i) {
    ASSERT_TRUE(allocator.allocate(32));
  }
  auto b = allocator.allocate(32);
  ASSERT_FALSE(allocator.allocate(32));
}

TEST(SegregatedFreelist, GoodSize) {
  segregated_freelist_allocator<malloc_allocator, 16, 32, 16, 1024> allocator;

  ASSERT_EQ(32, allocator.good_size(1));
  ASSERT_EQ(32, allocator.good_size(16));
  ASSERT_EQ(32, allocator.good_size(17));
  ASSERT_EQ(32, allocator.good_size(32));
  ASSERT_EQ(32, allocator.good_size(33));

  ASSERT_EQ(32, allocator.allocate(16).length);
  ASSERT_EQ(32, allocator.allocate(17).length);
  ASSERT_EQ(32, allocator.allocate(31).length);
  ASSERT_EQ(32, allocator.allocate(32).length);
}
