 /**
  * Reallocate a block of memory with a new size, with the start address 
  * being aligned to a multiple of \p align bytes.
  * \remarks The returned block of memory must be freed with AlignedFree.
  * \warning The alignment must be the same as initially passed to 
  *   AlignedMalloc.
  */
 void* AlignedRealloc (void* ptr, size_t size, 
   size_t align)
 {
 #if !defined(CS_NO_PTMALLOC)
   void* newPtr = ptmalloc_::ptrealloc (ptr, size);
   if ((newPtr != ptr)
     && ((((uintptr_t)newPtr) / align * align) != (uintptr_t)newPtr))
   {
     // Bah, alignment borked. Need to alloc again :(
     void* newPtrAligned = ptmalloc_::ptmemalign (align, size);
     memcpy (newPtrAligned, newPtr, size);
     ptfree (newPtr);
     newPtr = newPtrAligned;
   }
   return newPtr;
 #elif defined(CS_HAVE__ALIGNED_MALLOC)
   return _aligned_realloc (ptr, size, align);
 #else
   void* orgPtr = *(((void**)ptr) - 1);
   uintptr_t offsetToData = (uintptr_t)ptr - (uintptr_t)orgPtr;
   void* newPtr = cs_realloc (orgPtr, size + align + sizeof(void*));
   
   uintptr_t ptrInt = (intptr_t)newPtr;
   ptrInt = (ptrInt + align + sizeof(void*)) / align * align;
   uintptr_t newOffsetToData = ptrInt - (uintptr_t)newPtr;
   if (newOffsetToData != offsetToData)
   {
     // Ensure realloced data is aligned again
     memmove ((void*)(ptrInt), (void*)((uintptr_t)newPtr + offsetToData),
       size);
   }
   
   *(((void**)ptrInt) - 1) = newPtr;
   return (void*)ptrInt;
 #endif
 }