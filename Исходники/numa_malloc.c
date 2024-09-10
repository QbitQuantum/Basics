HANDLE
ReturnHeapHandle(
        VOID
        )
{
    HANDLE           hHeap;                     /* preferred heap handle to
                                                   return to caller */
    PROCESSOR_NUMBER CurrentProcessorNumber;    /* processor number associated
                                                   with calling thread */
    USHORT           CurrentNumaNodeNumber;     /* NUMA node number assocaited
                                                   with calling thread */

    /* determine NUMA status of system. */

    if (g_ulNumaStatus == NUMA_STATUS_UNKNOWN)
    {
        InitNumaHeapSupport();
        if (g_ulNumaStatus == NUMA_STATUS_NOT_NUMA)
        {
            return GetProcessHeap();
        }
    }
    else if (g_ulNumaStatus == NUMA_STATUS_NOT_NUMA)
    {
        /* not NUMA, return the process heap handle */
        return GetProcessHeap();
    }


    /* return the preferred heap handle from the TLS slot, if set.
       This is the commonly taken path. */

    hHeap = (HANDLE)TlsGetValue( g_dwTlsHeap );

    if (hHeap != NULL)
    {
        return hHeap;
    }


    /* preferred heap handle not yet set.
       determine the numa node we're executing on, and create a heap which
       is assigned to this node.
       one (soft) assumption that is made here is that thread affinity has
       been set such that threads do not move between NUMA nodes.
     */

    smalloc_GetCurrentProcessorNumberEx(&CurrentProcessorNumber);

    if (!smalloc_GetNumaProcessorNodeEx(&CurrentProcessorNumber, &CurrentNumaNodeNumber))
    {
        /* GetNumaProcessorNodeEx() can fail on WOW64/32bit if invoked
           against processor numbers > 32.
           this should never be reached for 64bit builds.
         */
        CurrentNumaNodeNumber = 0;
    }


    /* check if the NUMA node array slot already contains a heap */
    /* CurrentNumaNodeNumber cannot execeed count of heaps, as NUMA nodes
       cannot be added. */

    hHeap = g_hHeap[ CurrentNumaNodeNumber ];

    if (hHeap == NULL)
    {
        HANDLE hHeapPrior = NULL;
        ULONG  ulOption   = 2; /* HEAP_LFH */

        /* create a heap for this numa node
           defer creating the heap - while running on each node - to ensure
           the heap control structures get created on the local NUMA node.
         */

        hHeap = HeapCreate(0, 0, 0);

        if (hHeap == NULL)
        {
            /* just return the process heap.  We'll try to create a heap
               again next time */
            return GetProcessHeap();
        }

        /* make the new heap a low-fragmentation heap */

        HeapSetInformation(
                hHeap,
                0,          /* HeapCompatibilityInformation */
                &ulOption,
                sizeof(ulOption)
                );

        /* set the array slot entry for this NUMA node to contain the newly
           allocated heap */

        hHeapPrior = (HANDLE)InterlockedCompareExchangePointer(&(g_hHeap[CurrentNumaNodeNumber]), hHeap, NULL);
        if (hHeapPrior != NULL)
        {
            HeapDestroy( hHeap );
            hHeap = hHeapPrior;
        }
    }

    /* we reached here since there was no heap assigned to the TLS slot.
       Assign it. */
    TlsSetValue(g_dwTlsHeap, hHeap);

    return hHeap;
}