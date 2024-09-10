extern void*
CVMmemalignAlloc(size_t alignment, size_t size)
{
    CVMassert(alignment == WIN32_VIRTUAL_ALLOC_ALIGNMENT);
    return VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
}