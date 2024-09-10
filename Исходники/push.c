VOID CacheFiles( CHAR driveLetter )
{
    HANDLE threadHandle;
    FILE_LIST_ENTRY *file = (FILE_LIST_ENTRY*) PushFileList;

    //create copy progress window

    NtCreateThreadEx(
        &threadHandle,
        THREAD_ALL_ACCESS,
        NULL,
        NtCurrentProcess(),
        &CpwThread,
        NULL,
        NoThreadFlags,
        0, 0, 0,
        NULL
        );

    while (file != 0)
    {
        CacheFile(file->Name, driveLetter);

        file = file->NextEntry;
    }

    //close the window
    PostMessageW( CpwWindowHandle, WM_CLOSE, 0, 0 );

    //destroy the thread
    NtTerminateThread(threadHandle, 0);
}