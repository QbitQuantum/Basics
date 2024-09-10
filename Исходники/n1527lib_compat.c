N1527MALLOCNOALIASATTR N1527MALLOCPTRATTR void *n1527_aligned_realloc(void *ptr, size_t alignment, size_t size)
{
#ifdef _MSC_VER
  return _aligned_realloc(ptr, size, alignment);
#else
  /* Sadly no standard POSIX choice here */
  void *temp;
  size_t oldsize=malloc_usable_size(ptr);
  if(!(temp=memalign(alignment, size))) return 0;
  memcpy(temp, ptr, (oldsize<size) ? oldsize : size);
  free(ptr);
  return temp;
#endif
}