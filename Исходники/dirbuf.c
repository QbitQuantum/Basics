FSP_API BOOLEAN FspFileSystemAcquireDirectoryBuffer(PVOID *PDirBuffer,
    BOOLEAN Reset, PNTSTATUS PResult)
{
    FSP_FILE_SYSTEM_DIRECTORY_BUFFER *DirBuffer = *PDirBuffer;
    MemoryBarrier();

    if (0 == DirBuffer)
    {
        static SRWLOCK CreateLock = SRWLOCK_INIT;
        FSP_FILE_SYSTEM_DIRECTORY_BUFFER *NewDirBuffer;

        NewDirBuffer = MemAlloc(sizeof *NewDirBuffer);
        if (0 == NewDirBuffer)
            RETURN(STATUS_INSUFFICIENT_RESOURCES, FALSE);
        memset(NewDirBuffer, 0, sizeof *NewDirBuffer);
        InitializeSRWLock(&NewDirBuffer->Lock);
        AcquireSRWLockExclusive(&NewDirBuffer->Lock);

        AcquireSRWLockExclusive(&CreateLock);
        DirBuffer = *PDirBuffer;
        MemoryBarrier();
        if (0 == DirBuffer)
            *PDirBuffer = DirBuffer = NewDirBuffer;
        ReleaseSRWLockExclusive(&CreateLock);

        if (DirBuffer == NewDirBuffer)
            RETURN(STATUS_SUCCESS, TRUE);

        ReleaseSRWLockExclusive(&NewDirBuffer->Lock);
        MemFree(NewDirBuffer);
    }

    if (Reset)
    {
        AcquireSRWLockExclusive(&DirBuffer->Lock);

        DirBuffer->LoMark = 0;
        DirBuffer->HiMark = DirBuffer->Capacity;

        RETURN(STATUS_SUCCESS, TRUE);
    }

    RETURN(STATUS_SUCCESS, FALSE);
}