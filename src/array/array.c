#include "array.h"
#include <stdio.h>
#include <string.h>

/* Construct a darray with a set stride.
@param type_stride: size of the data type this array is intended to store.
@returns Newly constructed darray. */
darray _darray_construct(size_t type_stride) 
{
  darray array;
  array.size = 0;
  array.capacity = DARRAY_INITIAL_CAPACITY;
  array.stride = type_stride;
  array.data = malloc(DARRAY_INITIAL_CAPACITY * type_stride);
  return array;
}

/* Reallocated a darray to have a new capacity, copying over and freeing the old elements.
@param array: Pointer to the array.
@param new_capacity: The new capacity of the array. */
void _darray_reallocate(darray* array, size_t new_capacity) 
{
  const size_t stride = array->stride;
  const size_t mem_bytes = new_capacity * stride;
  void* new_data = malloc(mem_bytes);

  if(new_capacity < array->size)
    array->size = new_capacity;

  memcpy(new_data, array->data, array->size * array->stride);

  array->capacity = new_capacity;

  free(array->data);

  array->data = new_data;
}

/* Increase the capacity of the array given it's current capacity automatically.
@param array: Pointer to the array. */
void _darray_increase_capacity(darray* array) 
{
  const size_t current_capacity = array->capacity;
  size_t new_capacity;
  if(current_capacity < 5) {
    new_capacity = (current_capacity + 1) * 2; // big initial increase
  } else {
    new_capacity = (current_capacity * 3) >> 1; // x 1.5
  }
  _darray_reallocate(array, new_capacity);
}

/* Get a pointer to the element held at the array index. The stride of the array is used.
@param array: Pointer to the array.
@param index: Element to get.
@returns Pointer to the element. */
void* _darray_at(darray* array, size_t index) 
{
  if(index >= array->size) {
    #ifdef LOG_ARRAY_ERRORS
    printf("[ARRAY ERROR]: Out of bounds in _darray_at(). Attempting to get index %i when size of array is %i\n", index, array->size);
    #endif
    //abort();
  }
  return &((char*)array->data)[index * array->stride];
}