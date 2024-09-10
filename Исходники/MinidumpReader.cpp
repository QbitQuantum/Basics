int CMiniDumpReader::ReadMemoryListStream()
{
    LPVOID pStreamStart = NULL;
    ULONG uStreamSize = 0;
    MINIDUMP_DIRECTORY* pmd = NULL;
    BOOL bRead = FALSE;

    bRead = MiniDumpReadDumpStream(
        m_pMiniDumpStartPtr, 
        MemoryListStream, 
        &pmd, 
        &pStreamStart, 
        &uStreamSize);

    if(bRead)
    {
        MINIDUMP_MEMORY_LIST* pMemStream = (MINIDUMP_MEMORY_LIST*)pStreamStart;
        if(pMemStream!=NULL)
        {
            ULONG32 uNumberOfMemRanges = pMemStream->NumberOfMemoryRanges;
            ULONG i;
            for(i=0; i<uNumberOfMemRanges; i++)
            {
                MINIDUMP_MEMORY_DESCRIPTOR* pMemDesc = (MINIDUMP_MEMORY_DESCRIPTOR*)(&pMemStream->MemoryRanges[i]);
                MdmpMemRange mr;
                mr.m_u64StartOfMemoryRange = pMemDesc->StartOfMemoryRange;
                mr.m_uDataSize = pMemDesc->Memory.DataSize;
                mr.m_pStartPtr = (LPBYTE)m_pMiniDumpStartPtr+pMemDesc->Memory.Rva;

                m_DumpData.m_MemRanges.push_back(mr);
            }
        }
    }
    else    
    {
        return 1;
    }

    return 0;
}