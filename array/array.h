#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct darray {
    size_t size;
    size_t capacity;
    size_t stride;
    void* data;
} darray;

#define DARRAY_INITIAL_CAPACITY 1

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

  if(new_capacity < array->size)
    array->size = new_capacity;

  memcpy(new_data, array->data, array->size * array->stride);

  array->capacity = new_capacity;

  free(array->data);

  array->data = new_data;
}

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

void* _darray_at(darray* array, size_t index) 
{
  if(index >= array->size) {
    printf("out of bounds");
    abort();
  }
  return &((char*)array->data)[index * array->stride];
}

/* Get address of an element in the array at a specified index.
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being read.
@param index: Index of the element. Byte offset calculated by array's stride.
@returns Address of the element held in the array. */ 
#define darray_address_at(array, type, index) (type*)_darray_at(&array, index)

/* Get the value of an element in the array at a specified index.
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being read.
@param index: Index of the element. Byte offset calculated by array's stride.
@returns Value of the element held in the array. */
#define darray_at(array, type, index) *darray_address_at(array, type, index);

/* Add an element to the end of the array, and allocate more data if necessary.
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being added.
@param element: Element to add. */
#define darray_add(array, type, element)    \
if(array.size == array.capacity)            \
  _darray_increase_capacity(&array);        \
((type*)array.data)[array.size] = element;  \
array.size++







#endif