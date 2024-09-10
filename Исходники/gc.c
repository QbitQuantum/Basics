void *jl_gc_managed_realloc(void *d, size_t sz, size_t oldsz, int isaligned)
{
    if (allocd_bytes > collect_interval)
        jl_gc_collect();
    sz = (sz+15) & -16;
    void *b;
#ifdef _P64
    b = realloc(d, sz);
#elif defined(_OS_WINDOWS_)
    if (isaligned)
        b = _aligned_realloc(d, sz, 16);
    else
        b = realloc(d, sz);
#elif defined(__APPLE__)
    b = realloc(d, sz);
#else
    // TODO better aligned realloc here
    b = malloc_a16(sz);
    if (b != NULL) {
        memcpy(b, d, oldsz);
        if (isaligned) free_a16(d);
        else free(d);
    }
#endif
    if (b == NULL)
        jl_throw(jl_memory_exception);
    allocd_bytes += sz;
    return b;
}