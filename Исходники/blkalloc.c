PBL_BLOCK_DESCRIPTOR
MmBapFindBlockInformation (
    ULONG BlockId
    )
{
    ULONG EntryId;

    /* Find the block that matches */
    EntryId = BlockId;
    return BlTblFindEntry(MmBlockAllocatorTable,
                          MmBlockAllocatorTableEntries,
                          &EntryId,
                          MmBapCompareBlockAllocatorTableEntry,
                          UlongToPtr(EntryId),
                          NULL,
                          NULL,
                          NULL);
}