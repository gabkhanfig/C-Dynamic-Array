#include <stdio.h>
#include "array/array.h"


struct darray;

int main() {

  darray array = _darray_construct(sizeof(int));

  darray_add(array, int, 10);
  darray_add(array, int, 20);
  darray_add(array, int, 40);
  darray_add(array, int, 21);
  darray_add(array, int, 25);
  darray_add(array, int, 60);
  darray_add(array, int, 100);

  for(int i = 0; i < array.size; i++) {
    //void* elem = _darray_at(&array, i);
    //int element = *(int*)elem; 
    int element = darray_at(array, int, i);
    printf("array element %i = %i\n", i, element);
  }

  return 0;
}