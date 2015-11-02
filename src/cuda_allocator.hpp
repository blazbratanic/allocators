#ifndef CUDA_ALLOCATOR_HPP
#define CUDA_ALLOCATOR_HPP

#include "pool_allocator.hpp"
#include "cuda_freelist_allocator.hpp"
#include "bucket_allocator.hpp"

template <std::size_t Size>
using CFA = cuda_freelist_allocator<Size, 8, 1024>;
using cuda_allocator = pool_allocator<log_bucket_allocator<CFA, 1024, 2048 * 2048>>;

#endif CUDA_ALLOCATOR_HPP