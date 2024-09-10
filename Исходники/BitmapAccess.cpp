void* FreeImage_Aligned_Malloc(size_t amount, size_t alignment) {
	assert(alignment == FIBITMAP_ALIGNMENT);
	return _aligned_malloc(amount, alignment);
}