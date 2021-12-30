#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <cstdlib>

class HeapAllocator {
public:
  void* alloc(uint64_t size) const { return malloc(size); }
  void free(void* ptr) const { ::free(ptr); }
  void* realloc(void* ptr, uint64_t size) const { return ::realloc(ptr, size); }
};

using Allocator = HeapAllocator;

#endif /* COMMON_H */