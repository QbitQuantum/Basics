void* _aligned_recalloc(void* memblock, size_t num, size_t size, size_t alignment)
{
	return _aligned_offset_recalloc(memblock, num, size, alignment, 0);
}