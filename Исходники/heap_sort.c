void pop_heap(size_t n, int *heap) {
  if (n > 1) {
    swap(heap, 0, n - 1);
    heapify(n - 1, heap, 0);
  }
}