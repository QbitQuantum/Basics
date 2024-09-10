/*
 * flush_clwb -- (internal) flush the CPU cache, using clwb
 */
static void
flush_clwb(void *addr, size_t len)
{
	LOG(15, "addr %p len %zu", addr, len);

	uintptr_t uptr;

	/*
	 * Loop through cache-line-size (typically 64B) aligned chunks
	 * covering the given range.
	 */
	for (uptr = (uintptr_t)addr & ~(FLUSH_ALIGN - 1);
		uptr < (uintptr_t)addr + len; uptr += FLUSH_ALIGN) {
		_mm_clwb((char *)uptr);
	}
}