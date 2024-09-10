/******************************************************************************
 * ClearEventLogA [ADVAPI32.@]
 */
BOOL WINAPI
ClearEventLogA(IN HANDLE hEventLog,
               IN LPCSTR lpBackupFileName)
{
    ANSI_STRING BackupFileNameA;
    UNICODE_STRING BackupFileNameW;
    NTSTATUS Status;
    BOOL Result;

    TRACE("%p, %s\n", hEventLog, lpBackupFileName);

    if (lpBackupFileName == NULL)
    {
        RtlInitUnicodeString(&BackupFileNameW, NULL);
    }
    else
    {
        RtlInitAnsiString(&BackupFileNameA, lpBackupFileName);

        Status = RtlAnsiStringToUnicodeString(&BackupFileNameW,
                                              &BackupFileNameA,
                                              TRUE);
        if (!NT_SUCCESS(Status))
        {
            SetLastError(RtlNtStatusToDosError(Status));
            return FALSE;
        }
    }

    Result = ClearEventLogW(hEventLog,
                            BackupFileNameW.Buffer);

    RtlFreeUnicodeString(&BackupFileNameW);

    return Result;
}