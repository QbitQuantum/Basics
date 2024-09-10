// As you can see, we can free a single block of memory at any time without being inside a GC
void GCAllocator::Free(void * ptr, int size)
{
    CROSSNET_ASSERT(IsAligned(ptr), "");

    AllocStructure * freedPtr = static_cast<AllocStructure *>(ptr);
    int alignedSize = Align(size);
    InternalFree(freedPtr, alignedSize);
}