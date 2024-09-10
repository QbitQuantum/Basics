/*
 * @implemented
 */
BOOL
WINAPI
GetNamedPipeHandleStateA(HANDLE hNamedPipe,
                         LPDWORD lpState,
                         LPDWORD lpCurInstances,
                         LPDWORD lpMaxCollectionCount,
                         LPDWORD lpCollectDataTimeout,
                         LPSTR lpUserName,
                         DWORD nMaxUserNameSize)
{
    UNICODE_STRING UserNameW = { 0, 0, NULL };
    ANSI_STRING UserNameA;
    BOOL Ret;

    if(lpUserName != NULL)
    {
        UserNameW.MaximumLength = (USHORT)nMaxUserNameSize * sizeof(WCHAR);
        UserNameW.Buffer = RtlAllocateHeap(RtlGetProcessHeap(), 0, UserNameW.MaximumLength);
        if (UserNameW.Buffer == NULL)
        {
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            return FALSE;
        }

        UserNameA.Buffer = lpUserName;
        UserNameA.Length = 0;
        UserNameA.MaximumLength = (USHORT)nMaxUserNameSize;
    }

    Ret = GetNamedPipeHandleStateW(hNamedPipe,
                                   lpState,
                                   lpCurInstances,
                                   lpMaxCollectionCount,
                                   lpCollectDataTimeout,
                                   UserNameW.Buffer,
                                   nMaxUserNameSize);
    if (Ret && lpUserName != NULL)
    {
        NTSTATUS Status;

        RtlInitUnicodeString(&UserNameW, UserNameW.Buffer);
        Status = RtlUnicodeStringToAnsiString(&UserNameA, &UserNameW, FALSE);
        if (!NT_SUCCESS(Status))
        {
            BaseSetLastNTError(Status);
            Ret = FALSE;
        }
    }

    if (UserNameW.Buffer != NULL)
    {
        RtlFreeHeap(RtlGetProcessHeap(), 0, UserNameW.Buffer);
    }

    return Ret;
}