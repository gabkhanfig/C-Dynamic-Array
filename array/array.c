/*
#include "array.h";
#include <string.h>

darray _darray_construct(size_t type_stride) 
{
  darray array;
  array.size = 0;
  array.capacity = DARRAY_INITIAL_CAPACITY;
  array.stride = type_stride;
  array.data = malloc(DARRAY_INITIAL_CAPACITY);
  return array;
}

void _darray_reallocate(darray* array, size_t new_capacity) 
{
  const size_t stride = array->stride;
  const size_t mem_bytes = new_capacity * stride;
  void* new_data = malloc(mem_bytes);

  memcpy(new_data, array->data, array->capacity);

  if(new_capacity < array->size)
    array->size = new_capacity;

  array->capacity = new_capacity;

  free(array->data);

  array->data = new_data;
}
*/
