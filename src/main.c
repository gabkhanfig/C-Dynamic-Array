#include <stdio.h>
#include "array/array.h"
#include <time.h>

int main() 
{
  darray array = darray_construct(int);
  int elements[] = {3, 1, 4, 6, 1, 45, 124, 3, 5 };
  darray_add(array, int, 91);
  darray_add_elements(array, elements, 12);
  //darray_set_at(array, int, 1, 4);
  for(int i = 0; i < 10; i++) {
    darray_add(array, int, i);
  }
  for(int i = 0; i < array.size; i++) {
    printf("%i, ", darray_value_at(array, int, i));
  }
  
  return 0;
}