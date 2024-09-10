BOOL WINAPI ResilientCloseHandle(
    HANDLE hObject)
{
    BOOL Success;
    DWORD LastError;
    DWORD HandleFlags = 0, FileNameLen;
    WCHAR FileNameBuf[sizeof "\\\\?\\GLOBALROOT" - 1 + 1024] = L"\\\\?\\GLOBALROOT";

    if (GetHandleInformation(hObject, &HandleFlags) &&
        (HANDLE_FLAG_PROTECT_FROM_CLOSE & HandleFlags))
    {
        SetHandleInformation(hObject,
            HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);
        FileNameLen = GetFinalPathNameByHandle(hObject,
            FileNameBuf + sizeof "\\\\?\\GLOBALROOT" - 1, 1023,
            FILE_NAME_OPENED | VOLUME_NAME_NT);
        if (0 == FileNameLen || FileNameLen >= 1024)
            HandleFlags = 0;
    }

    Success = CloseHandle(
        hObject);
    LastError = GetLastError();

    if (Success)
    {
        if (HANDLE_FLAG_PROTECT_FROM_CLOSE & HandleFlags)
            WaitDeletePending(FileNameBuf);
    }

    SetLastError(LastError);
    return Success;
}