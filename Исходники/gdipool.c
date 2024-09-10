static
VOID
GdiPoolDeleteSection(PGDI_POOL pPool, PGDI_POOL_SECTION pSection)
{
    NTSTATUS status;
    SIZE_T cjSize = 0;

    /* Should not have any allocations */
    if (pSection->cAllocCount != 0)
    {
        DPRINT1("There are %lu allocations left, section=%p, pool=%p\n",
                pSection->cAllocCount, pSection, pPool);
        DBG_DUMP_EVENT_LIST(&pPool->slhLog);
        ASSERT(FALSE);
    }

    /* Release the virtual memory */
    status = ZwFreeVirtualMemory(NtCurrentProcess(),
                                 &pSection->pvBaseAddress,
                                 &cjSize,
                                 MEM_RELEASE);
    ASSERT(NT_SUCCESS(status));

    /* Free the section object */
    EngFreeMem(pSection);
}