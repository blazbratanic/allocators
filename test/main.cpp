#include "cuda_allocator.hpp"

#include <iostream>
#include <chrono>
#include <vector>


int main() {
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
      void* ptr;
      cudaMalloc(&ptr, 1024 * 1024);
      cudaFree(ptr);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "1000 allocations and deallocations took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << "ms\n";
  }

  cuda_allocator a;
  {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
      auto b = a.allocate(1024 * 1024);
      a.deallocate(b);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "1000 allocations and deallocations took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                     .count()
              << "ms\n";
  }

  for (int s = 10; s < 20; ++s) {
    a.allocate(1 << s);
  }
  return 0;
}