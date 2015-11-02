#ifndef BUCKET_ALLOCATOR_HPP
#define BUCKET_ALLOCATOR_HPP

#include "segregator.hpp"

template <template<std::size_t> class Allocator, std::size_t MinSize, std::size_t Size,
          bool Terminate = false>
struct log_bucket_allocator_impl {
  typedef segregator<Size / 2,
                     typename log_bucket_allocator_impl<Allocator, MinSize, Size / 2,
                                               (Size / 2 < MinSize)>::type,
                     Allocator<Size>> type;
};

template <template<std::size_t> class Allocator, std::size_t MinSize, std::size_t Size>
struct log_bucket_allocator_impl<Allocator, MinSize, Size, true> {
  typedef Allocator<Size> type;
};

template <template<std::size_t> class Allocator, std::size_t MinSize, std::size_t MaxSize>
using log_bucket_allocator =
    typename log_bucket_allocator_impl<Allocator, MinSize, MaxSize>::type;

#endif