BOOL
CFrfr2::
InitIndex(
    FRFR2_IGA_HEADER   *Header,
    PBYTE               EntryBuffer,
    ULONG               EntrySize,
    PBYTE               FileNameBuffer,
    ULONG               FileNameSize
)
{
    ULONG               Length, FileNameOffset, FileCount, MaxFileCount;
    ULONG               BeginOffset;
    PWCHAR              FileName;
    MY_FILE_ENTRY_BASE *pEntry, *pEntryBase;

    UNREFERENCED_PARAMETER(Header);

    FileCount       = 0;
    MaxFileCount    = 0x100;
    pEntryBase = (MY_FILE_ENTRY_BASE *)Alloc(MaxFileCount * sizeof(*m_Index.pEntry), HEAP_ZERO_MEMORY);
    if (pEntryBase == NULL)
        return FALSE;

    pEntry          = pEntryBase;
    BeginOffset     = file.GetCurrentPos64();
    FileNameOffset  = GetCompactInteger(EntryBuffer, &Length);
    for (LONG SizeOfEntry = EntrySize - Length; SizeOfEntry > 0; ++FileCount)
    {
        ULONG   Offset2;
        LONG    FileNameLength;

        pEntry->Offset.QuadPart = GetCompactInteger(EntryBuffer, &Length) + BeginOffset;
        SizeOfEntry            -= Length;
        pEntry->Size.QuadPart   = GetCompactInteger(EntryBuffer, &Length);
        SizeOfEntry            -= Length;

        FileName        = pEntry->FileName;
        Offset2         = GetCompactInteger(EntryBuffer, &Length);
        SizeOfEntry    -= Length;
        FileNameLength  = Offset2 - FileNameOffset;
        FileNameSize   -= FileNameLength;

        if (SizeOfEntry < 0)
            FileNameLength += FileNameSize;

        for (; FileNameLength > 0; FileNameLength -= Length)
        {
            *FileName++ = GetCompactInteger(FileNameBuffer, &Length);
        }

        *FileName = 0;

        FileNameOffset  = Offset2;

        if (FileCount == MaxFileCount)
        {
            MaxFileCount *= 2;
            pEntryBase = (MY_FILE_ENTRY_BASE *)ReAlloc(pEntryBase, MaxFileCount * sizeof(*m_Index.pEntry), HEAP_ZERO_MEMORY);
            if (pEntryBase == NULL)
                return FALSE;

            pEntry = pEntryBase + FileCount;
        }

        *(PULONG_PTR)&pEntry += m_Index.cbEntrySize;
    }

    m_Index.pEntry = pEntryBase;
    m_Index.FileCount.QuadPart = FileCount;
    m_Index.pEntry = (MY_FILE_ENTRY_BASE *)ReAlloc(m_Index.pEntry, m_Index.FileCount.LowPart * sizeof(*m_Index.pEntry));

    return m_Index.pEntry != NULL;
}