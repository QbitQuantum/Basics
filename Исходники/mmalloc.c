void* MikMod_realloc(void *data, size_t size)
{
	return realloc(data, size);
	
#if 0
	if (data)
	{
#if defined __MACH__
		void *d = realloc(data, size);
		if (d)
		{
			return d;
		}
		return 0;
#elif (defined _WIN32 || defined _WIN64) && !defined(_WIN32_WCE)
		return _aligned_realloc(data, size, ALIGN_STRIDE);
#else
		unsigned char *newPtr = (unsigned char *)realloc(get_pointer(data), size + ALIGN_STRIDE + sizeof(void*));
		return align_pointer(newPtr, ALIGN_STRIDE);
#endif
	}
	return MikMod_malloc(size);
#endif
}