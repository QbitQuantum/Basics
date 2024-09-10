void* tsk_realloc_aligned(void * ptr, tsk_size_t size, tsk_size_t alignment)
{
#if TSK_UNDER_WINDOWS && !TSK_UNDER_WINDOWS_CE && !TSK_UNDER_WINDOWS_RT
	return _aligned_realloc(ptr, size, alignment);
#else
	tsk_free_aligned(ptr);
	return tsk_malloc_aligned(size, alignment);
#endif
}