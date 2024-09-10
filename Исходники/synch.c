HANDLE
WINAPI
OpenWaitableTimerA(
    DWORD dwDesiredAccess,
    BOOL bInheritHandle,
    LPCSTR lpTimerName
)
{
    PUNICODE_STRING Unicode;
    ANSI_STRING AnsiString;
    NTSTATUS Status;

    if ( ARGUMENT_PRESENT(lpTimerName) ) {
        Unicode = &NtCurrentTeb()->StaticUnicodeString;
        RtlInitAnsiString(&AnsiString,lpTimerName);
        Status = RtlAnsiStringToUnicodeString(Unicode,&AnsiString,FALSE);
        if ( !NT_SUCCESS(Status) ) {
            if ( Status == STATUS_BUFFER_OVERFLOW ) {
                SetLastError(ERROR_FILENAME_EXCED_RANGE);
            }
            else {
                BaseSetLastNTError(Status);
            }
            return NULL;
        }
    }
    else {
        BaseSetLastNTError(STATUS_INVALID_PARAMETER);
        return NULL;
    }

    return OpenWaitableTimerW(
               dwDesiredAccess,
               bInheritHandle,
               (LPCWSTR)Unicode->Buffer
           );
}