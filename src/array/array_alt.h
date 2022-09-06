#ifndef ARRAY_ALT_H
#define ARRAY_ALT_H

#include <stdlib.h>

/*
array.h implementation appears to be faster. Run with no optimizations
100 million insertions:
array     - 0.397 cpu sec
array_alt - 0.836 cpu sec

perhaps this is due to all of the extra overhead needed to be done for offset checking? 
*/

typedef struct darray_alt {
  void* data;
} darray_alt;

typedef struct darray_alt_header {
  size_t size;
  size_t capacity;
  size_t stride;
} darray_alt_header;

extern darray_alt _darray_alt_construct(size_t stride);
extern darray_alt_header* _darray_alt_get_header(darray_alt* array);
extern void _darray_alt_reallocate(darray_alt* array, size_t new_capacity);
extern void _darray_alt_increase_capacity(darray_alt* array);
extern void* _darray_alt_at(darray_alt* array, size_t index);

#define darray_alt_construct(type) _darray_alt_construct(sizeof(type))

#define darray_alt_pointer_at(array, type, index) (type*)_darray_alt_at(&array, index)

#define darray_alt_value_at(array, type, index) *darray_alt_pointer_at(array, type, index)

#define darray_alt_add(array, type, element)                        \
darray_alt_header* _header_arr = _darray_alt_get_header(&array);    \
if(_header_arr->size == _header_arr->capacity)                      \
  _darray_alt_increase_capacity(&array);                            \
_header_arr = _darray_alt_get_header(&array);                       \
type* array_data = (type*)(array.data + sizeof(darray_alt_header)); \
(array_data[_header_arr->size]) = element;                          \
_header_arr->size++   












#endif