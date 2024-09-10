static TheCustomHeapType * initializeCustomHeap (void)
{
#if !defined(_WIN32)
  createKey();
  assert (pthread_getspecific (theHeapKey) == NULL);
#endif
  // Allocate a per-thread heap.
  TheCustomHeapType * heap;
  size_t sz = sizeof(TheCustomHeapType) + sizeof(double);
  void * mh = getMainHoardHeap()->malloc(sz);
  heap = new ((char *) mh) TheCustomHeapType (getMainHoardHeap());

  // Store it in the appropriate thread-local area.
#if defined(_WIN32)
  TlsSetValue (LocalTLABIndex, heap);
#else
  int r = pthread_setspecific (theHeapKey, (void *) heap);
  assert (!r);
#endif

  return heap;
}