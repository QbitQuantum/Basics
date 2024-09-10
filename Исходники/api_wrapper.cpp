void* Aligned_Realloc(void* ptr, size_t size, size_t align)
{
#ifdef __GNUC__
	return posix_memalign(ptr, align, size);
#else
	return _aligned_realloc(ptr, size, align);
#endif
}