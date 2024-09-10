HANDLE InternalCreateCallbackThread(
    HANDLE hProcess,
    DWORD lpfn,
    DWORD dwData)
{
    LONG BasePriority;
    HANDLE hThread, hToken;
    PTOKEN_DEFAULT_DACL lpDaclDefault;
    TOKEN_DEFAULT_DACL daclDefault;
    ULONG cbDacl;
    SECURITY_ATTRIBUTES attrThread;
    SECURITY_DESCRIPTOR sd;
    DWORD idThread;
    NTSTATUS Status;

    hThread = NULL;

    Status = NtOpenProcessToken(hProcess, TOKEN_QUERY, &hToken);
    if (!NT_SUCCESS(Status)) {
        KdPrint(("NtOpenProcessToken failed, status = %x\n", Status));
        return NULL;
    }

    cbDacl = 0;
    NtQueryInformationToken(hToken,
            TokenDefaultDacl,
            &daclDefault,
            sizeof(daclDefault),
            &cbDacl);

    EnterCrit();  // to synchronize heap
    lpDaclDefault = (PTOKEN_DEFAULT_DACL)LocalAlloc(LMEM_FIXED, cbDacl);
    LeaveCrit();

    if (lpDaclDefault == NULL) {
        KdPrint(("LocalAlloc failed for lpDaclDefault"));
        goto closeexit;
    }

    Status = NtQueryInformationToken(hToken,
            TokenDefaultDacl,
            lpDaclDefault,
            cbDacl,
            &cbDacl);
    if (!NT_SUCCESS(Status)) {
        KdPrint(("NtQueryInformationToken failed, status = %x\n", Status));
        goto freeexit;
    }

    if (!NT_SUCCESS(RtlCreateSecurityDescriptor(&sd,
            SECURITY_DESCRIPTOR_REVISION1))) {
        UserAssert(FALSE);
        goto freeexit;
    }

    RtlSetDaclSecurityDescriptor(&sd, TRUE, lpDaclDefault->DefaultDacl, TRUE);

    attrThread.nLength = sizeof(attrThread);
    attrThread.lpSecurityDescriptor = &sd;
    attrThread.bInheritHandle = FALSE;

    GetLastError();
    hThread = CreateRemoteThread(hProcess,
        &attrThread,
        0L,
        (LPTHREAD_START_ROUTINE)lpfn,
        (LPVOID)dwData,
        0,
        &idThread);

    if (hThread != NULL) {
        BasePriority = THREAD_PRIORITY_HIGHEST;
        NtSetInformationThread(hThread,
                               ThreadBasePriority,
                               &BasePriority,
                               sizeof(LONG));
    }

freeexit:
    EnterCrit();  // to synchronize heap
    LocalFree((HANDLE)lpDaclDefault);
    LeaveCrit();

closeexit:
    NtClose(hToken);

    return hThread;
}