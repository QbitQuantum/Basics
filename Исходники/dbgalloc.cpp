// Called just before process exit to report stats and check for memory
// leakages etc.
void __stdcall DbgAllocReport(char * pString, BOOL fDone, BOOL fDoPrintf)
{
    if (!g_HeapInitialized)
        return;

    if (g_LogStats || g_LogDist || g_DetectLeaks || g_UsageByAllocator)
        LOG((LF_DBGALLOC, LL_ALWAYS, "------ Allocation Stats ------\n"));

    // Print out basic statistics.
    if (g_LogStats) {
        LOG((LF_DBGALLOC, LL_ALWAYS, "\n"));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Alloc calls    : %u\n", (int)g_AllocStats.m_Allocs));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Alloc failures : %u\n", (int)g_AllocStats.m_AllocFailures));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Alloc 0s       : %u\n", (int)g_AllocStats.m_ZeroAllocs));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Alloc bytes    : %u\n", (int)g_AllocStats.m_AllocBytes));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Free calls     : %u\n", (int)g_AllocStats.m_Frees));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Free NULLs     : %u\n", (int)g_AllocStats.m_NullFrees));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Free bytes     : %u\n", (int)g_AllocStats.m_FreeBytes));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Leaked allocs  : %u\n", (int)(g_AllocStats.m_Allocs - g_AllocStats.m_AllocFailures) -
             (g_AllocStats.m_Frees - g_AllocStats.m_NullFrees)));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Leaked bytes   : %u\n", (int)g_AllocStats.m_AllocBytes - g_AllocStats.m_FreeBytes));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Max allocation : %u\n", (int)g_AllocStats.m_MaxAlloc));
    }

    // Print out allocation size distribution statistics.
    if (g_LogDist) {
        LOG((LF_DBGALLOC, LL_ALWAYS, "\n"));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Alloc distrib  :\n"));
        for (unsigned i = 0; i < CDA_DIST_BUCKETS; i++)
            LOG((LF_DBGALLOC, LL_ALWAYS, "  [%3u,%3u] : %u\n", i * CDA_DIST_BUCKET_SIZE,
                 (i * CDA_DIST_BUCKET_SIZE) + (CDA_DIST_BUCKET_SIZE - 1),
                 (int)g_AllocBuckets[i]));
        LOG((LF_DBGALLOC, LL_ALWAYS, "  [%3u,---] : %u\n", CDA_MAX_DIST_SIZE + 1, (int)g_LargeAllocs));
    }

    // Print out the table of top allocators. Table is pre-sorted, the first
    // NULL entry indicates the end of the valid list.
    if (g_UsageByAllocator && g_TopAllocators) {
        LOG((LF_DBGALLOC, LL_ALWAYS, "\n"));
        LOG((LF_DBGALLOC, LL_ALWAYS, "Top allocators :\n"));
        for (unsigned i = 0; i < min(CDA_TOP_ALLOCATORS, g_TopAllocatorsSlots); i++) {
            if (g_TopAllocators[i].m_EIP == NULL)
                break;
            LOG((LF_DBGALLOC, LL_ALWAYS, "  %2u: %08X %s\n",
                 i + 1,
                 g_TopAllocators[i].m_EIP,
                 DbgSymbolize(g_TopAllocators[i].m_EIP)));
            LOG((LF_DBGALLOC, LL_ALWAYS, "       %u allocations, %u bytes total, %u bytes average size\n",
                 g_TopAllocators[i].m_Count,
                 (unsigned)g_TopAllocators[i].m_TotalBytes,
                 (unsigned)(g_TopAllocators[i].m_TotalBytes / g_TopAllocators[i].m_Count)));
        }
    }

    // Print out info for all leaked packets.
    if (g_DetectLeaks) {

        DbgAllocHeader *h = g_AllocListFirst;
        int fHaveLeaks = (h!=NULL);

        if (h) {

            // Tell the Log we had memory leaks
            LOG((LF_DBGALLOC, LL_ALWAYS, "\n"));
            LOG((LF_DBGALLOC, LL_ALWAYS, "Detected memory leaks!\n"));
            LOG((LF_DBGALLOC, LL_ALWAYS, "Leaked packets :\n"));

            // Tell the console we had memory leaks
            if (fDoPrintf)
            {
                printf("Detected memory leaks!\n");
                if (pString != NULL)
                    printf("%s\n", pString);
                    
                printf("Leaked packets :\n");
            }
        }

        while (h) {
            char buffer1[132];
            char buffer2[32];
            sprintf(buffer1, "#%u %08X:%u ", h->m_SN, CDA_HEADER_TO_DATA(h), h->m_Length);
            unsigned i;
            for (i = 0; i < 16; i++) {
                if (i < h->m_Length)
                    sprintf(buffer2, "%02X", (BYTE)CDA_DATA(h, i));
                else
                    strcpy(buffer2, "  ");
                if ((i % 4) == 3)
                    strcat(buffer2, " ");
                strcat(buffer1, buffer2);
            }
            for (i = 0; i < min(16, h->m_Length); i++) {
                sprintf(buffer2, "%c", (CDA_DATA(h, i) < 32) || (CDA_DATA(h, i) > 127) ? '.' : CDA_DATA(h, i));
                strcat(buffer1, buffer2);
            }
            LOG((LF_DBGALLOC, LL_ALWAYS, "%s\n", buffer1));
            if (fDoPrintf)
                printf("%s\n", buffer1);
            
            if (g_CallStackDepth == 1) {
                LOG((LF_DBGALLOC, LL_ALWAYS, " Allocated at %08X %s\n",
                     CDA_ALLOC_STACK(h, 0), DbgSymbolize(CDA_ALLOC_STACK(h, 0))));

            if (fDoPrintf)
                printf(" Allocated at %08X %s\n",
                     CDA_ALLOC_STACK(h, 0), DbgSymbolize(CDA_ALLOC_STACK(h, 0)));
            } else {
                LOG((LF_DBGALLOC, LL_ALWAYS, " Allocation call stack:\n"));
                if (fDoPrintf)
                    printf(" Allocation call stack:\n");
                for (unsigned i = 0; i < g_CallStackDepth; i++) {
                    if (CDA_ALLOC_STACK(h, i) == NULL)
                        break;
                    LOG((LF_DBGALLOC, LL_ALWAYS, "  %08X %s\n",
                         CDA_ALLOC_STACK(h, i), DbgSymbolize(CDA_ALLOC_STACK(h, i))));
                    if (fDoPrintf)
                        printf("  %08X %s\n",
                             CDA_ALLOC_STACK(h, i), DbgSymbolize(CDA_ALLOC_STACK(h, i)));
                }
            }
            wchar_t buf[256];
            GetModuleFileNameW(h->m_hmod, buf, 256);
            LOG((LF_DBGALLOC, LL_ALWAYS, " Base, name: %08X %S\n\n", h->m_hmod, buf));
            if (fDoPrintf)
                printf(" Base, name: %08X %S\n\n", h->m_hmod, buf);
            h = h->m_Next;
        }

        if (fDoPrintf)
            fflush(stdout);

        if (fHaveLeaks && g_AssertOnLeaks)
            _ASSERTE(!"Detected memory leaks!");

    }

    if (g_LogStats || g_LogDist || g_DetectLeaks || g_UsageByAllocator) {
        LOG((LF_DBGALLOC, LL_ALWAYS, "\n"));
        LOG((LF_DBGALLOC, LL_ALWAYS, "------------------------------\n"));
    }

    if (fDone)
    {
        DbgUnloadSymbols();
        DeleteCriticalSection(&g_AllocMutex);
        // We won't be doing any more of our debug allocation stuff
        g_DbgEnabled=0;
    }
}