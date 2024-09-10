void * __cdecl _recalloc_base(void * memblock, size_t count, size_t size)
{
    void * retp = NULL;
    size_t  size_orig = 0, old_size = 0;

    /* ensure that (size * count) does not overflow */
    if (count > 0)
    {
        _VALIDATE_RETURN_NOEXC((_HEAP_MAXREQ / count) >= size, ENOMEM, NULL);
    }
    size_orig = size * count;
    if (memblock != NULL)
        old_size = _msize(memblock);
    retp = _realloc_base(memblock, size_orig);
    if (retp != NULL && old_size < size_orig)
    {
        memset ((char*)retp + old_size, 0, size_orig - old_size);
    }
    return retp;
}