/**
 * Reallocate memory, with alignment.
 */
void *
_mesa_align_realloc(void *oldBuffer, size_t oldSize, size_t newSize,
                    unsigned long alignment)
{
#if defined(_WIN32) && defined(_MSC_VER)
   (void) oldSize;
   return _aligned_realloc(oldBuffer, newSize, alignment);
#else
   const size_t copySize = (oldSize < newSize) ? oldSize : newSize;
   void *newBuf = _mesa_align_malloc(newSize, alignment);
   if (newBuf && oldBuffer && copySize > 0) {
      memcpy(newBuf, oldBuffer, copySize);
   }
   if (oldBuffer)
      _mesa_align_free(oldBuffer);
   return newBuf;
#endif
}