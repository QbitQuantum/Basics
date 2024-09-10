ULONG
NTAPI
MiFreePoolPages(IN PVOID StartingVa)
{
    PMMPTE PointerPte, StartPte;
    PMMPFN Pfn1, StartPfn;
    PFN_COUNT FreePages, NumberOfPages;
    KIRQL OldIrql;
    PMMFREE_POOL_ENTRY FreeEntry, NextEntry, LastEntry;
    ULONG i, End;
    ULONG_PTR Offset;

    //
    // Handle paged pool
    //
    if ((StartingVa >= MmPagedPoolStart) && (StartingVa <= MmPagedPoolEnd))
    {
        //
        // Calculate the offset from the beginning of paged pool, and convert it
        // into pages
        //
        Offset = (ULONG_PTR)StartingVa - (ULONG_PTR)MmPagedPoolStart;
        i = (ULONG)(Offset >> PAGE_SHIFT);
        End = i;

        //
        // Now use the end bitmap to scan until we find a set bit, meaning that
        // this allocation finishes here
        //
        while (!RtlTestBit(MmPagedPoolInfo.EndOfPagedPoolBitmap, End)) End++;

        //
        // Now calculate the total number of pages this allocation spans. If it's
        // only one page, add it to the S-LIST instead of freeing it
        //
        NumberOfPages = End - i + 1;
        if ((NumberOfPages == 1) &&
                (ExQueryDepthSList(&MiPagedPoolSListHead) < MiPagedPoolSListMaximum))
        {
            InterlockedPushEntrySList(&MiPagedPoolSListHead, StartingVa);
            return 1;
        }

        /* Delete the actual pages */
        PointerPte = MmPagedPoolInfo.FirstPteForPagedPool + i;
        FreePages = MiDeleteSystemPageableVm(PointerPte, NumberOfPages, 0, NULL);
        ASSERT(FreePages == NumberOfPages);

        //
        // Acquire the paged pool lock
        //
        KeAcquireGuardedMutex(&MmPagedPoolMutex);

        //
        // Clear the allocation and free bits
        //
        RtlClearBit(MmPagedPoolInfo.EndOfPagedPoolBitmap, End);
        RtlClearBits(MmPagedPoolInfo.PagedPoolAllocationMap, i, NumberOfPages);

        //
        // Update the hint if we need to
        //
        if (i < MmPagedPoolInfo.PagedPoolHint) MmPagedPoolInfo.PagedPoolHint = i;

        //
        // Release the lock protecting the bitmaps
        //
        KeReleaseGuardedMutex(&MmPagedPoolMutex);

        //
        // And finally return the number of pages freed
        //
        return NumberOfPages;
    }