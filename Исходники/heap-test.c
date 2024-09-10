static int arrayTest(void)
{
  int **matrix, i;

  heapInit();
  expectHeapEmpty();

  // Allocate room for 3 pointers.
  matrix = (int **)heapAlloc(3 * sizeof(int *));
  expectHeapSize(HEAP_SIZE
                 - (3 * (sizeof(int *))) - 1 // 3 pointers and 1 alloc byte
                 - 0);
  
  // Allocate 5 integers in each array.
  for (i = 0; i < 3; i ++) {
    matrix[i] = (int *)heapAlloc(5 * sizeof(int));
  }
  expectHeapSize(HEAP_SIZE
                 // 3 pointers and 1 alloc byte
                 - (3 * (sizeof(int *))) - 1
                 // 3 arrays of 5 int's plus an alloc byte each
                 - 3 * ((5 * sizeof(int)) + 1) 
                 - 0);

  // Free the arrays.
  for (i = 0; i < 3; i ++) {
    heapFree(matrix[i]);
  }
  expectHeapSize(HEAP_SIZE
                 - (3 * (sizeof(int *))) - 1 // 3 pointers and 1 alloc byte
                 - 0);
  
  // Free the pointers.
  heapFree(matrix);
  expectHeapEmpty();

  return 0;
}