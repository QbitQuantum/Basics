NTSTATUS
AustereInitialize()
{
    RtlZeroMemory(&AustereHeap, sizeof(XENCRSH_HEAP));

    AustereHeap.BigHeapStart = __AustereSection;
    AustereHeap.NumHeapPages = AUSTERE_HEAP_PAGES;

    // ensure big heap is page aligned
    if ( ((ULONG_PTR)AustereHeap.BigHeapStart & (PAGE_SIZE - 1)) ) {
        AustereHeap.BigHeapStart = __Round(AustereHeap.BigHeapStart, PAGE_SIZE);
        --AustereHeap.NumHeapPages;
    }
    
    LogVerbose("HEAP: [%p - %p) (%d pages)\n", AustereHeap.BigHeapStart, AustereHeap.BigHeapStart + (AustereHeap.NumHeapPages * PAGE_SIZE), AustereHeap.NumHeapPages);

    AustereHeap.BigHeapCursor = 0;
    AustereHeap.HeapBlockSizes[0] = AustereHeap.NumHeapPages | FREE_CHUNK;
    AustereHeap.HeadSubHeap = NULL;

    return STATUS_SUCCESS;
}