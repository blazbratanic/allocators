#ifndef CUDA_ALLOCATOR_HPP
#define CUDA_ALLOCATOR_HPP

#include "pool_allocator.hpp"
#include "cuda_freelist_allocator.hpp"
#include "segregator.hpp"

template <std::size_t Size> using CFA = cuda_freelist_allocator<Size>;

using cuda_allocator =
    pool_allocator <
    segregator<1024 * 1024,
               segregator<512 * 1024,
                          segregator<256 * 1024,
                                     segregator<128 * 1024, CFA<128 * 1024>,
                                                CFA<256 * 1024>>,
                                     CFA<512 * 1024>>,
                          CFA<1024 * 1024>>,
               CFA<2048 * 1024>>>;

#endif CUDA_ALLOCATOR_HPP