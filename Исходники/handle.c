/*
 * @implemented
 */
BOOL
WINAPI
GetHandleInformation(IN HANDLE hObject,
                     OUT LPDWORD lpdwFlags)
{
    OBJECT_HANDLE_ATTRIBUTE_INFORMATION HandleInfo;
    ULONG BytesWritten;
    NTSTATUS Status;
    DWORD Flags;

    hObject = TranslateStdHandle(hObject);

    if (IsConsoleHandle(hObject))
    {
        /* FIXME: GetConsoleHandleInformation required */
        UNIMPLEMENTED;
        BaseSetLastNTError(STATUS_NOT_IMPLEMENTED);
        return FALSE;
    }

    Status = NtQueryObject(hObject,
                           ObjectHandleFlagInformation,
                           &HandleInfo,
                           sizeof(OBJECT_HANDLE_ATTRIBUTE_INFORMATION),
                           &BytesWritten);
    if (!NT_SUCCESS(Status))
    {
        BaseSetLastNTError(Status);
        return FALSE;
    }

    Flags = 0;
    if (HandleInfo.Inherit) Flags |= HANDLE_FLAG_INHERIT;
    if (HandleInfo.ProtectFromClose) Flags |= HANDLE_FLAG_PROTECT_FROM_CLOSE;
    *lpdwFlags = Flags;
    return TRUE;
}