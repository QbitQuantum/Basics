void* __cdecl calloc(
    size_t num,
    size_t size
) {
    void* retp;
    size *= num;

    for (;;) {
        retp = HeapAlloc(_crtheap, HEAP_ZERO_MEMORY, size);

        if (retp || _newmode == 0) {
            return retp;
        }

        /* call installed new handler */
        if (!_callnewh(size)) {
            return NULL;
        }

        /* new handler was successful -- try to allocate again */
    }
}