void ExecutablePool::systemRelease(const ExecutablePool::Allocation& alloc)
{ 
    VirtualFree(alloc.pages, 0, MEM_RELEASE); 
}