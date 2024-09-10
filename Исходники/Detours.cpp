static PDETOUR_TRAMPOLINE detour_alloc_trampoline(PBYTE pbTarget)
{
    // We have to place trampolines within +/- 2GB of target.
    // The allocation code assumes that

    PDETOUR_TRAMPOLINE pLo = (PDETOUR_TRAMPOLINE)
        ((pbTarget > (PBYTE)0x7ff80000)
         ? pbTarget - 0x7ff80000 : (PBYTE)(ULONG_PTR)DETOUR_REGION_SIZE);
    PDETOUR_TRAMPOLINE pHi = (PDETOUR_TRAMPOLINE)
        ((pbTarget < (PBYTE)0xffffffff80000000)
         ? pbTarget + 0x7ff80000 : (PBYTE)0xfffffffffff80000);
    DETOUR_TRACE(("[%p..%p..%p]\n", pLo, pbTarget, pHi));

    PDETOUR_TRAMPOLINE pTrampoline = NULL;

    // Insure that there is a default region.
    if (s_pRegion == NULL && s_pRegions != NULL) {
        s_pRegion = s_pRegions;
    }

    // First check the default region for an valid free block.
    if (s_pRegion != NULL && s_pRegion->pFree != NULL &&
        s_pRegion->pFree >= pLo && s_pRegion->pFree <= pHi) {

      found_region:
        pTrampoline = s_pRegion->pFree;
        // do a last sanity check on region.
        if (pTrampoline < pLo || pTrampoline > pHi) {
            return NULL;
        }
        s_pRegion->pFree = (PDETOUR_TRAMPOLINE)pTrampoline->pbRemain;
        memset(pTrampoline, 0xcc, sizeof(*pTrampoline));
        return pTrampoline;
    }

    // Then check the existing regions for a valid free block.
    for (s_pRegion = s_pRegions; s_pRegion != NULL; s_pRegion = s_pRegion->pNext) {
        if (s_pRegion != NULL && s_pRegion->pFree != NULL &&
            s_pRegion->pFree >= pLo && s_pRegion->pFree <= pHi) {
            goto found_region;
        }
    }

    // We need to allocate a new region.

    // Round pbTarget down to 64K block.
    pbTarget = pbTarget - (PtrToUlong(pbTarget) & 0xffff);

    // First we search down (within the valid region)

    DETOUR_TRACE((" Looking for free region below %p:\n", pbTarget));

    PBYTE pbTry;
    for (pbTry = pbTarget; pbTry > (PBYTE)pLo;) {
        MEMORY_BASIC_INFORMATION mbi;

        DETOUR_TRACE(("  Try %p\n", pbTry));
        if (pbTry >= (PBYTE)(ULONG_PTR)0x70000000 &&
            pbTry <= (PBYTE)(ULONG_PTR)0x80000000) {
            // Skip region reserved for system DLLs.
            pbTry = (PBYTE)(ULONG_PTR)(0x70000000 - DETOUR_REGION_SIZE);
        }
        if (!VirtualQuery(pbTry, &mbi, sizeof(mbi))) {
            break;
        }

        DETOUR_TRACE(("  Try %p => %p..%p %6x\n",
                      pbTry,
                      mbi.BaseAddress,
                      (PBYTE)mbi.BaseAddress + mbi.RegionSize - 1,
                      mbi.State));

        if (mbi.State == MEM_FREE && mbi.RegionSize >= DETOUR_REGION_SIZE) {
            s_pRegion = (DETOUR_REGION*)VirtualAlloc(pbTry,
                                                     DETOUR_REGION_SIZE,
                                                     MEM_COMMIT|MEM_RESERVE,
                                                     PAGE_EXECUTE_READWRITE);
            if (s_pRegion != NULL) {
              alloced_region:
                s_pRegion->dwSignature = DETOUR_REGION_SIGNATURE;
                s_pRegion->pFree = NULL;
                s_pRegion->pNext = s_pRegions;
                s_pRegions = s_pRegion;
                DETOUR_TRACE(("  Allocated region %p..%p\n\n",
                              s_pRegion, ((PBYTE)s_pRegion) + DETOUR_REGION_SIZE - 1));

                // Put everything but the first trampoline on the free list.
                PBYTE pFree = NULL;
                pTrampoline = ((PDETOUR_TRAMPOLINE)s_pRegion) + 1;
                for (int i = DETOUR_TRAMPOLINES_PER_REGION - 1; i > 1; i--) {
                    pTrampoline[i].pbRemain = pFree;
                    pFree = (PBYTE)&pTrampoline[i];
                }
                s_pRegion->pFree = (PDETOUR_TRAMPOLINE)pFree;
                goto found_region;
            }
            else {
                DETOUR_TRACE(("Error: %p %d\n", pbTry, GetLastError()));
                break;
            }
        }
        pbTry = (PBYTE)mbi.AllocationBase - DETOUR_REGION_SIZE;
    }

    DETOUR_TRACE((" Looking for free region above %p:\n", pbTarget));

    for (pbTry = pbTarget; pbTry < (PBYTE)pHi;) {
        MEMORY_BASIC_INFORMATION mbi;

        if (pbTry >= (PBYTE)(ULONG_PTR)0x70000000 &&
            pbTry <= (PBYTE)(ULONG_PTR)0x80000000) {
            // Skip region reserved for system DLLs.
            pbTry = (PBYTE)(ULONG_PTR)(0x80000000 + DETOUR_REGION_SIZE);
        }
        if (!VirtualQuery(pbTry, &mbi, sizeof(mbi))) {
            break;
        }

        DETOUR_TRACE(("  Try %p => %p..%p %6x\n",
                      pbTry,
                      mbi.BaseAddress,
                      (PBYTE)mbi.BaseAddress + mbi.RegionSize - 1,
                      mbi.State));

        if (mbi.State == MEM_FREE && mbi.RegionSize >= DETOUR_REGION_SIZE) {
            ULONG_PTR extra = ((ULONG_PTR)pbTry) & (DETOUR_REGION_SIZE - 1);
            if (extra != 0) {
                // WinXP64 returns free areas that aren't REGION aligned to
                // 32-bit applications.
                ULONG_PTR adjust = DETOUR_REGION_SIZE - extra;
                mbi.RegionSize -= adjust;
                ((PBYTE&)mbi.BaseAddress) += adjust;
                DETOUR_TRACE(("--Try %p => %p..%p %6x\n",
                              pbTry,
                              mbi.BaseAddress,
                              (PBYTE)mbi.BaseAddress + mbi.RegionSize - 1,
                              mbi.State));
                pbTry = (PBYTE)mbi.BaseAddress;
            }
            s_pRegion = (DETOUR_REGION*)VirtualAlloc(pbTry,
                                                     DETOUR_REGION_SIZE,
                                                     MEM_COMMIT|MEM_RESERVE,
                                                     PAGE_EXECUTE_READWRITE);
            if (s_pRegion != NULL) {
                goto alloced_region;
            }
            else {
                DETOUR_TRACE(("Error: %p %d\n", pbTry, GetLastError()));
            }
        }

        pbTry = (PBYTE)mbi.BaseAddress + mbi.RegionSize;
    }

    DETOUR_TRACE(("Couldn't find available memory region!\n"));
    return NULL;
}