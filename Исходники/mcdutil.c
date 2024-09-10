UCHAR *MCDAlloc(UINT size)
{
    return (UCHAR *)EngAllocMem(FL_ZERO_MEMORY, size, MCD_ALLOC_TAG);
}