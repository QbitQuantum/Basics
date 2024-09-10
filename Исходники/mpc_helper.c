void* FF_aligned_realloc(void *ptr,size_t size,size_t alignment)
{
	if (!ptr)
		return FF_aligned_malloc(size,alignment);
	else
		if (size==0)
		{
			FF_aligned_free(ptr);
			return NULL;
		}
		else
			return _aligned_realloc(ptr,size,alignment);
}