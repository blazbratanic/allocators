#ifndef CUDA_FREELIST_ALLOCATOR
#define CUDA_FREELIST_ALLOCATOR

#include <cuda.h>
#include <cuda_runtime.h>

#include <cstddef>
#include <cassert>
#include <memory>
#include <stdexcept>

#include "blk.hpp"

#define GPU_ERRCHK(ans) \
  { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char* file, int line) {
  if (code != cudaSuccess) {
    fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file,
            line);
    throw std::runtime_error(cudaGetErrorString(code));
  }
}

template <std::size_t Size, std::size_t AllocationBlockCount = 8,
          std::size_t MaxSize = 1024>
class CudaFreelistAllocator {
  static_assert(Size % 256 == 0,
                "CUDA memory is aligned to at least 256 bytes");

 public:
  blk allocate(std::size_t size) {
    assert(size <= Size);
    if (free_blocks_.empty()) {
      if ((blocks_.size() + 1) * AllocationBlockCount <= MaxSize) {
        void* ptr;
        GPU_ERRCHK(cudaMalloc(&ptr, AllocationBlockCount * Size));
        blocks_.emplace_back(blocks_::value_type(ptr));
        segregate(ptr);
      } else {
        return{ nullptr, 0 };
      }
    }

    auto ptr = free_blocks_.back();
    free_blocks_.pop_back();
    return{ ptr, size };
  }

  void deallocate(blk b) { free_blocks_.emplace_back(b.ptr); }

  void deallocate_all() {
    free_blocks_.clear();
    for (auto e : blocks_) {
      segregate(e.get());
    }
  }

  bool owns(blk b) {
    for (auto e : blocks_) {
      if (e.get() <= blk.ptr && blk.ptr < e.get() + Size) return true;
    }
    return false;
  }

  std::size_t good_size() const { return Size; }

 private:
  void segregate(void* ptr) {
    for (int i = 0; i < AllocationBlockCount) {
      free_blocks_.emplace_back(ptr + i * Size);
    }
  }

  std::vector<std::unique_ptr<void, [](void* p) { GPU_ERRCHK(cudaFree(p)); }>>
      blocks_;
  std::vector<void*> free_blocks_;
};

#undef GPU_ERRCHK

#endif