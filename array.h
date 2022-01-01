#include <cstdint>

#include "common.h"

template <typename T>
struct Array {
  uint32_t capacity;
  uint32_t count;
  T* data;
};

//-----------------------------------------------------------------------------
template <typename T>
void init_array(Array<T>* array) {
  array->count = 0;
  array->capacity = 0;
  array->data = nullptr;
}

//-----------------------------------------------------------------------------
template <typename T>
void free_array(Array<T>* array, Allocator& allocator) {
  allocator.free(array->data);
  init_array(array);
}

//-----------------------------------------------------------------------------
template <typename T>
void write_array(Array<T>* array, T value, Allocator& allocator) {
  // Do we need to reallocate array?
  if (array->capacity < array->count + 1) {
    array->capacity = ((array->capacity) < 8 ? 8 : (array->capacity) * 2);
    array->data =
        static_cast<T*>(allocator.realloc(array->data, array->capacity * sizeof(T)));
  }

  array->data[array->count] = value;
  array->count++;
}

using ByteArray = Array<uint8_t>;
using UIntArray = Array<uint32_t>;
