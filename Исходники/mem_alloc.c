void *rax_realloc(void *p, size_t size, boolean needsMemoryAlignment) 
{  
  //it's actually not that easy to implement an aligned realloc
  //because we need to know the size of the array pointed to by 
  //the pointer passed as argument
  //hence I added this boolean flag that should increase programmer 
  //awareness about this issue
  void 
    *ptr = (void *)NULL;

  if(needsMemoryAlignment)
    {
      assert(0);
      return (void*)NULL;
    }
  else
    {
#ifndef WIN32      
      ptr = realloc(p, size);
#else
      ptr = _aligned_realloc(p, size, BYTE_ALIGNMENT);
#endif
    }

  if(ptr == (void*)NULL) 
    {
      outOfMemory();
      assert(0);
    }

  return ptr;
}