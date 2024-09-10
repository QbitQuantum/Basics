void* DefaultAllocateAligned(size_t size, size_t alignment)
{
	return _aligned_malloc(size, alignment);
}