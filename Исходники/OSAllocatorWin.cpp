void OSAllocator::decommit(void* address, size_t bytes)
{
    bool result = VirtualFree(address, bytes, MEM_DECOMMIT);
    if (!result)
        CRASH();
}