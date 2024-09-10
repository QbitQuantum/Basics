VOID MemHeapMin(VOID)
  {
  heapLock();
  _uheapmin(hp);
  heapUnlock();
  }