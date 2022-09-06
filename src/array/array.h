#ifndef ARRAY_H
#define ARRAY_H

#define LOG_ARRAY_ERRORS

#include <stdlib.h>

typedef struct darray {
    size_t size;
    size_t capacity;
    size_t stride;
    void* data;
} darray;

extern darray _darray_construct(const size_t type_stride);
extern void _darray_reallocate(darray* array, const size_t new_capacity);
extern void _darray_increase_capacity(darray* array);
extern void* _darray_at(darray* array, const size_t index);
extern void _darray_append_elements(darray* array, const void* elements, const size_t amount);

/* Construct a darray with the stride set to the inputted data type. 
@param type: The intended type of the darray to store (used for stride). 
@returns Newly constructed darray. */
#define darray_construct(type) _darray_construct(sizeof(type))

/* Get address of an element in the array at a specified index.
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being read.
@param index: Index of the element. Byte offset calculated by array's stride.
@returns Address of the element held in the array. */ 
#define darray_pointer_at(array, type, index) (type*)_darray_at(&array, index)

/* Get the value of an element in the array at a specified index.
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being read.
@param index: Index of the element. Byte offset calculated by array's stride.
@returns Value of the element held in the array. */
#define darray_value_at(array, type, index) *darray_pointer_at(array, type, index)

/* Set the value at a specified index. 
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being used.
@param index: Index of the element to set. Byte offset calculated by array's stride. 
@param element: The value to set. */
#define darray_set_at(array, type, index, element) darray_value_at(array, type, index) = element

/* Add an element to the end of the array, and allocate more data if necessary.
@param array: The array that is being index. Pass in directly (not as pointer).
@param type: Type of data being added.
@param element: Element to add. */
#define darray_add(array, type, element)    \
if(array.size == array.capacity)            \
  _darray_increase_capacity(&array);        \
((type*)array.data)[array.size] = element;  \
array.size++

/* Add multiple elements to the end of the array at once, allocating as much space as necessary.
Assumes each element of the elements passed in have the same size as the array's stride.
@param array: The array that is being index. Pass in directly (not as pointer).
@param elements: Beginning of elements. 
@param amount: Amount of elements of the type to add. */
#define darray_add_elements(array, elements, amount) _darray_append_elements(&array, elements, amount)


#endif