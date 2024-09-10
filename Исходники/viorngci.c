static DWORD ToDosError(NTSTATUS status)
{
    DWORD error = NO_ERROR;
    HMODULE ntdll;
    RtlNtStatusToDosErrorFunc RtlNtStatusToDosError;

    ntdll = LoadLibrary(L"Ntdll.dll");
    if (ntdll != NULL)
    {
        RtlNtStatusToDosError = (RtlNtStatusToDosErrorFunc)
            GetProcAddress(ntdll, "RtlNtStatusToDosError");

        if (RtlNtStatusToDosError != NULL)
        {
            error = RtlNtStatusToDosError(status);
        }
        else
        {
            error = GetLastError();
            SetupWriteTextLogError(SetupGetThreadLogToken(),
                TXTLOG_INSTALLER,
                TXTLOG_ERROR,
                error,
                "RtlNtStatusToDosError function not found.");
        }
    }
    else
    {
        error = GetLastError();
        SetupWriteTextLogError(SetupGetThreadLogToken(),
            TXTLOG_INSTALLER,
            TXTLOG_ERROR,
            error,
            "Failed to load ntdll.dll.");
    }

    return error;
}