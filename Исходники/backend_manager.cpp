/*
 * flush_clflush -- (internal) flush the CPU cache, using clflush
 */
static inline void flush_clflush(const void *addr, size_t len) {
  uintptr_t uptr;

  // Loop through cache-line-size (typically 64B) aligned chunks
  // covering the given range.
  for (uptr = (uintptr_t)addr & ~(FLUSH_ALIGN - 1);
       uptr < (uintptr_t)addr + len; uptr += FLUSH_ALIGN)
    _mm_clflush((char *)uptr);
}