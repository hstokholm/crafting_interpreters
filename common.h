#ifndef COMMON_H
#define COMMON_H

#include <cstdint>
#include <cstdlib>

#define DEBUG_TRACE_EXECUTION 1
#define STACK_MAX 256

class HeapAllocator {
 public:
  void* alloc(uint64_t size) const { return malloc(size); }
  void free(void* ptr) const { ::free(ptr); }
  void* realloc(void* ptr, uint64_t size) const { return ::realloc(ptr, size); }
};

using Allocator = HeapAllocator;

#endif /* COMMON_H */