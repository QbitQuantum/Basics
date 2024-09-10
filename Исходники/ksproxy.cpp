KSDDKAPI
HRESULT
WINAPI
KsSynchronousDeviceControl(
    HANDLE     Handle,
    ULONG      IoControl,
    PVOID      InBuffer,
    ULONG      InLength,
    PVOID      OutBuffer,
    ULONG      OutLength,
    PULONG     BytesReturned)
{
    OVERLAPPED Overlapped;
    DWORD Transferred;

    /* zero overlapped */
    RtlZeroMemory(&Overlapped, sizeof(OVERLAPPED));

    /* create notification event */
    Overlapped.hEvent = CreateEventW(NULL, TRUE, FALSE, NULL);

    if (!Overlapped.hEvent)
    {
        /* failed */
        return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, GetLastError());
    }

    if (!DeviceIoControl(Handle, IoControl, InBuffer, InLength, OutBuffer, OutLength, BytesReturned, &Overlapped))
    {
        /* operation failed */
        if (GetLastError() != ERROR_IO_PENDING)
        {
            /* failed */
            CloseHandle(Overlapped.hEvent);
            return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, GetLastError());
        }
    }

    /* get result of pending operation */
    if (!GetOverlappedResult(Handle, &Overlapped, &Transferred, TRUE))
    {
        /* failed */
        CloseHandle(Overlapped.hEvent);
        return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, GetLastError());
    }

    /* store number of bytes transferred */
    *BytesReturned = Transferred;

    /* close event object */
    CloseHandle(Overlapped.hEvent);

    /* done */
    return NOERROR;
}