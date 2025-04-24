#ifndef Darray_algos_h
#define Darray_algos_h

#include <lcthw/DArray.h>

typedef int (*DArray_compare)(const void *a, const void *b);

int DArray_qsort(DArray *array, DArray_compare cmp);

int Qsort(void **contents, size_t left, size_t right, size_t size, DArray_compare cmp);

int DArray_heapsort(DArray *array, DArray_compare cmp);

void heapsort(void **contents, size_t start, size_t end, size_t size, DArray_compare cmp);

void heapify(void **contents, size_t index, size_t length);

int DArray_mergesort(DArray *array, DArray_compare cmp);

void mergesort(void **contents, size_t left, size_t right, size_t size, DArray_compare cmp, void **tmp);

#endif
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 
