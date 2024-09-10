static NTSTATUS PhpWfsoThreadStart(
    _In_ PVOID Parameter
    )
{
    HANDLE eventHandle;
    LARGE_INTEGER timeout;

    eventHandle = Parameter;

    timeout.QuadPart = -(LONGLONG)UInt32x32To64(5, PH_TIMEOUT_SEC);
    NtWaitForSingleObject(eventHandle, FALSE, &timeout);

    return STATUS_SUCCESS;
}