void *__cilkrts_realloc(void *ptr, size_t size)
{
#ifdef _WIN32
    return _aligned_realloc(ptr, size, PREFERRED_ALIGNMENT);
#else
    return realloc(ptr, size);
#endif
}