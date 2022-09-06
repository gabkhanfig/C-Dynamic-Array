#include "array_alt.h"
#include <stdio.h>
#include <string.h>

darray_alt _darray_alt_construct(size_t stride) 
{
  darray_alt array;
  darray_alt_header header;
  header.size = 0;
  header.capacity = 1;
  header.stride = stride;

  array.data = malloc(sizeof(header) + header.capacity * stride);
  *(darray_alt_header*)array.data = header;
  return array;
}

darray_alt_header* _darray_alt_get_header(darray_alt* array) 
{
    return (darray_alt_header*)array->data;
}

void _darray_alt_reallocate(darray_alt* array, size_t new_capacity) 
{
  //printf("reallocating darray alternate with new capacity of %i\n", new_capacity);
  darray_alt_header header = *_darray_alt_get_header(array);

  const size_t mem_bytes = new_capacity * header.stride;
  void* new_data = malloc(sizeof(header) + mem_bytes);

  if(new_capacity < header.size)
    header.size = new_capacity;

  header.capacity = new_capacity;

  //memcpy(new_data + sizeof(header), array->data + sizeof(header), header.size * header.stride);
  *(darray_alt_header*)new_data = header;
  //*(int*)(new_data + sizeof(header)) = 88;
  //printf("new darray header data: %i, %i, %i\n", (*(darray_alt_header*)new_data).size, (*(darray_alt_header*)new_data).capacity, (*(darray_alt_header*)new_data).stride);
  //printf("and data index 0 integer is %i\n", *(int*)(new_data + sizeof(header)));
  free(array->data);

  array->data = new_data;
}

void _darray_alt_increase_capacity(darray_alt* array) 
{
  const size_t current_capacity = _darray_alt_get_header(array)->capacity;
  size_t new_capacity;
  if(current_capacity < 5) {
    new_capacity = (current_capacity + 1) * 2; // big initial increase
  } else {
    new_capacity = (current_capacity * 3) >> 1; // x 1.5
  }
  _darray_alt_reallocate(array, new_capacity);
}

void* _darray_alt_at(darray_alt* array, size_t index) 
{
  const size_t size = _darray_alt_get_header(array)->size;
  if(index >= size) {
    printf("out of bounds\n");
    //abort();
  }
  return array->data + (sizeof(darray_alt_header) + index * _darray_alt_get_header(array)->stride);
}

