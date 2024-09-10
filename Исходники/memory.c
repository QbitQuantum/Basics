LPVOID
DRVALLOC(
    DWORD  cbAlloc
    )
/*++

Routine Description:

    This function will allocate local memory. It will possibly allocate extra
    memory and fill this with debugging information for the debugging version.

Arguments:

    cb - The amount of memory to allocate

Return Value:

    NON-NULL - A pointer to the allocated memory

    FALSE/NULL - The operation failed. Extended error status is available
    using GetLastError.

--*/
{
    LPDWORD  pMem = NULL;

#if DBG
    DWORD    cbOld = 0;

    cbOld = DWORD_ALIGN_UP(cbAlloc);
    cbAlloc = cbOld + 4 * sizeof(DWORD);
#endif

#if NTGDIKM
    pMem = (LPDWORD)EngAllocMem(0, cbAlloc,gulMemID);
#else
    pMem = (LPDWORD)HeapAlloc( hHeap, HEAP_ZERO_MEMORY, cbAlloc );
#endif

#if DBG
    if (!pMem)
    {
        EngAcquireSemaphore(hsem);
        gFailCount++;
        gbFailAllocs = TRUE;
        EngReleaseSemaphore(hsem);
        return (LPVOID)pMem;

    }
    else
    {
        EngAcquireSemaphore(hsem);
        gAllocCount++;
        EngReleaseSemaphore(hsem);

        pMem[0] = cbOld;

    #if (_MSC_VER >= 1000)
        pMem[1] =  (DWORD)_ReturnAddress();
    #else
        //
        // Put in a bogus value to prevent 0 from being read back.
        //
        pMem[1] = 0xf987654f;
    #endif

        *(LPDWORD)((LPBYTE)&pMem[2] + cbOld)=0xdeadbeef;

        return (LPVOID)&pMem[2];
    }
#endif

    return (LPVOID)pMem;
}