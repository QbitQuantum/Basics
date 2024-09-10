CF_PRIVATE Boolean _CFWriteBytesToFileAsync(CFURLRef url, const void *bytes, CFIndex length) {
    char path[CFMaxPathSize];
    if (!CFURLGetFileSystemRepresentation(url, true, (uint8_t *)path, CFMaxPathSize)) {
        return false;
    }

    wchar_t wpath[CFMaxPathSize];
    int convertedLength = MultiByteToWideChar(CP_UTF8, 0, path, CFMaxPathSize, wpath, CFMaxPathSize);
    if (0 == convertedLength) {
        unsigned error = GetLastError();
        CFLog(kCFLogLevelWarning, CFSTR("_CFWriteBytesToFileAsync failed to convert the path (error %u)"), error);
        return false;
    }

    HANDLE fileHandle = NULL;
    CREATEFILE2_EXTENDED_PARAMETERS createExParams;
    createExParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
    createExParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    createExParams.dwFileFlags = FILE_FLAG_OVERLAPPED;
    createExParams.dwSecurityQosFlags = 0;
    createExParams.lpSecurityAttributes = NULL;
    createExParams.hTemplateFile = NULL;

    OVERLAPPED* overlapped = (OVERLAPPED*)calloc(1, sizeof(OVERLAPPED));

    if ((fileHandle = CreateFile2(wpath, GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS, &createExParams)) == INVALID_HANDLE_VALUE) {
        unsigned error = GetLastError();
        CFLog(kCFLogLevelWarning, CFSTR("_CFWriteBytesToFileAsync failed to open the file (error %u)"), error);
        free(overlapped);
        return false;
    }

    PTP_IO threadPoolIo = CreateThreadpoolIo(fileHandle, _threadpoolCallback, NULL, NULL);
    StartThreadpoolIo(threadPoolIo);

    if (!WriteFile(fileHandle, bytes, length, NULL, overlapped)) {
        unsigned error = GetLastError();
        if (ERROR_IO_PENDING != error) {
            CFLog(kCFLogLevelWarning, CFSTR("_CFWriteBytesToFileAsync failed to write to the file (error %u)"), error);
            CloseHandle(fileHandle);
            CancelThreadpoolIo(threadPoolIo);
            CloseThreadpoolIo(threadPoolIo);
            free(overlapped);
            return false;
        }
    }

    CloseHandle(fileHandle);

    return true;
}