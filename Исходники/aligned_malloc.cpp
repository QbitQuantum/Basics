size_t __cdecl iso_aligned_msize(void *ptr, size_t alignment, size_t offset)
{
    size_t header_size;     /* Size of the header block */
    size_t footer_size;     /* Size of the footer block */
    size_t total_size;      /* total size of the allocated block */
    size_t user_size;       /* size of the user block*/
    uintptr_t uintptr_offset;   /* keep the alignment of the data block */
                            /* after the sizeof(void*) aligned pointer */
                            /* to the beginning of the allocated block */

    /* HEADER SIZE + FOOTER SIZE = uintptr_offset + ALIGNMENT + SIZE OF A POINTER*/
    /* HEADER SIZE + USER SIZE + FOOTER SIZE = TOTAL SIZE */
    _ASSERT(ptr != NULL);

    ALIGN_BLOCK_HEADER *pBlockHdr = NULL; /* points to the beginning of the allocated block*/
    pBlockHdr = (ALIGN_BLOCK_HEADER *)((uintptr_t)ptr & ~(sizeof(uintptr_t) - 1)) - 1;

#ifdef __linux__
    total_size = malloc_usable_size(pBlockHdr->pvAlloc);
#else
    total_size = _msize(pBlockHdr->pvAlloc);
#endif
    header_size = (uintptr_t)ptr - (uintptr_t)(pBlockHdr->pvAlloc);
    uintptr_offset = (0 - offset) & (sizeof(uintptr_t) - 1);

    /* The align cannot be smaller than the sizeof(uintptr_t) */
    alignment = (alignment > sizeof(uintptr_t) ? alignment : sizeof(uintptr_t)) -1;
    footer_size = alignment + sizeof(ALIGN_BLOCK_HEADER) + uintptr_offset - header_size;
    user_size = total_size - header_size - footer_size;
    return user_size;
}