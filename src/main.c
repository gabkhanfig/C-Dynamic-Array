#include <stdio.h>
#include "array/array.h"
#include "array/array_alt.h"
#include <time.h>

const int iterations = 10;
const int insertions = 10000;

int main() {

  printf("Start\n\n");
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  for(int iteration = 0; iteration < iterations; iteration++) {
    darray array = darray_construct(int);
 
    for(int i = 0; i < insertions; i++) {
      darray_add(array, int, i * 2);
      printf("Verifying added element %i... Expected: %i, Found: %i\n", i, i * 2, darray_at(array, int, i));
    }
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time for default array: %Lf\n\n", cpu_time_used);

  start = clock();
  for(int iteration = 0; iteration < iterations; iteration++) {
    darray_alt array = _darray_alt_construct(sizeof(int));

    for(int i = 0; i < insertions; i++) {
      //const darray_alt_header header = *_darray_alt_get_header(&array);
      //printf("Doing an add %i. ", i);
      //printf("Header data: %i, %i, %i\n", header.size, header.capacity, header.stride);
      darray_alt_add(array, int, i * 2);
      printf("Verifying added element %i... Expected: %i, Found: %i\n", i, i * 2, darray_alt_value_at(array, int, i));
    }
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Elapsed time for alt array: %Lf\n\n", cpu_time_used);

  printf("Completed\n");
  return 0;
}