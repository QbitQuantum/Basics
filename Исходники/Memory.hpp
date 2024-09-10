    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    // Allocates the specified amount of bytes from virtual memory.
    // Tries to allocate the memory from the specified NUMA node.
    static void* AllocateNuma(size_t size, unsigned int prefferedNode) {
        Statistics::BlockAllocated();

#if defined(PLATFORM_WINDOWS)
        if(VirtualAllocExNumaFct != nullptr) {
            // Under Vista+, allocate using the special NUMA method.
            return VirtualAllocExNuma(GetCurrentProcess(), nullptr, size,
                                      MEM_COMMIT, PAGE_READWRITE, prefferedNode);
        }
        else {
            return VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE);
        }
#else
        static_assert(false, "Not yet implemented.");
#endif
    }