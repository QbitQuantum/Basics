//----------------------------------------------------------------------
//-- a little cross platform numa allocator
//-- use the existing theron defines for convenience
//----------------------------------------------------------------------
inline void *AllocOnNode(const long node, const size_t size)
{

#if THERON_NUMA

#if THERON_WINDOWS

    #if _WIN32_WINNT >= 0x0600
    return VirtualAllocExNuma(
        GetCurrentProcess(),
        NULL,
        size,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE,
        node
    );
    #else
    return NULL;
    #endif

#elif THERON_GCC

    if ((numa_available() < 0))
    {
        return NULL;
    }

    return numa_alloc_onnode(size, node);

#endif

#endif // THERON_NUMA

    return NULL;
}