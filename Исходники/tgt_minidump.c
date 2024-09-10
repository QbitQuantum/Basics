static BOOL WINAPI tgt_process_minidump_read(HANDLE hProcess, const void* addr, 
                                             void* buffer, DWORD len, DWORD* rlen)
{
    ULONG               size;
    MINIDUMP_DIRECTORY* dir;
    void*               stream;

    if (!PRIVATE(dbg_curr_process)->mapping) return FALSE;
    if (MiniDumpReadDumpStream(PRIVATE(dbg_curr_process)->mapping,
                               MemoryListStream, &dir, &stream, &size))
    {
        MINIDUMP_MEMORY_LIST*   mml = (MINIDUMP_MEMORY_LIST*)stream;
        MINIDUMP_MEMORY_DESCRIPTOR* mmd = &mml->MemoryRanges[0];
        int                     i;

        for (i = 0; i < mml->NumberOfMemoryRanges; i++, mmd++)
        {
            if (mmd->StartOfMemoryRange <= (DWORD_PTR)addr &&
                (DWORD_PTR)addr < mmd->StartOfMemoryRange + mmd->Memory.DataSize)
            {
                len = min(len, mmd->StartOfMemoryRange + mmd->Memory.DataSize - (DWORD_PTR)addr);
                memcpy(buffer, 
                       (char*)PRIVATE(dbg_curr_process)->mapping + mmd->Memory.Rva + (DWORD_PTR)addr - mmd->StartOfMemoryRange,
                       len);
                if (rlen) *rlen = len;
                return TRUE;
            }
        }
    }
    /* FIXME: this is a dirty hack to let the last frame in a bt to work
     * However, we need to check who's to blame, this code or the current 
     * dbghelp!StackWalk implementation
     */
    if ((DWORD_PTR)addr < 32)
    {
        memset(buffer, 0, len); 
        if (rlen) *rlen = len;
        return TRUE;
    }
    return FALSE;
}