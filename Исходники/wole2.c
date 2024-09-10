BOOL GetThreadIDHTASKALIAS(
    DWORD  dwThreadID32,
    HTASKALIAS *ha
) {
    OBJECT_ATTRIBUTES   obja;
    THREAD_BASIC_INFORMATION ThreadInfo;
    HANDLE      hThread;
    NTSTATUS    Status;
    FILETIME    ftDummy;
    CLIENT_ID   cid;

    InitializeObjectAttributes(
            &obja,
            NULL,
            0,
            NULL,
            0 );

    cid.UniqueProcess = 0;      // Don't know it, 0 means any process
    cid.UniqueThread  = (HANDLE)dwThreadID32;

    Status = NtOpenThread(
                &hThread,
                THREAD_QUERY_INFORMATION,
                &obja,
                &cid );

    if ( !NT_SUCCESS(Status) ) {
#if DBG
        DbgPrint("WOW32: Could not get open thread handle\n");
#endif
        return( FALSE );
    }

    Status = NtQueryInformationThread(
        hThread,
        ThreadBasicInformation,
        (PVOID)&ThreadInfo,
        sizeof(THREAD_BASIC_INFORMATION),
        NULL
        );

    ha->dwProcessID32 = (DWORD)ThreadInfo.ClientId.UniqueProcess;
    ha->dwThreadID32  = dwThreadID32;

    GetThreadTimes( hThread,
        &ha->ftCreationTime,
        &ftDummy,
        &ftDummy,
        &ftDummy );

    Status = NtClose( hThread );
    if ( !NT_SUCCESS(Status) ) {
#if DBG
        DbgPrint("WOW32: Could not close thread handle\n");
        DbgBreakPoint();
#endif
        return( FALSE );
    }
    return( TRUE );
}