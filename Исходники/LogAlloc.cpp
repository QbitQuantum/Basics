void*
replace_memalign(size_t aAlignment, size_t aSize)
{
  AutoLock lock(sLock);
  void* ptr = sFuncs->memalign(aAlignment, aSize);
  if (ptr) {
    FdPrintf(sFd, "%zu %zu memalign(%zu,%zu)=%p\n", GetPid(), GetTid(),
             aAlignment, aSize, ptr);
  }
  return ptr;
}