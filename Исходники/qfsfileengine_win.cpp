/*
    \internal
*/
bool QFSFileEnginePrivate::nativeOpen(QIODevice::OpenMode openMode)
{
    Q_Q(QFSFileEngine);

    // All files are opened in share mode (both read and write).
    DWORD shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

    int accessRights = 0;
    if (openMode & QIODevice::ReadOnly)
        accessRights |= GENERIC_READ;
    if (openMode & QIODevice::WriteOnly)
        accessRights |= GENERIC_WRITE;


    // WriteOnly can create files, ReadOnly cannot.
    DWORD creationDisp = (openMode & QIODevice::WriteOnly) ? OPEN_ALWAYS : OPEN_EXISTING;
    // Create the file handle.
#ifndef Q_OS_WINRT
    SECURITY_ATTRIBUTES securityAtts = { sizeof(SECURITY_ATTRIBUTES), NULL, FALSE };
    fileHandle = CreateFile((const wchar_t*)fileEntry.nativeFilePath().utf16(),
                            accessRights,
                            shareMode,
                            &securityAtts,
                            creationDisp,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
#else // !Q_OS_WINRT
    fileHandle = CreateFile2((const wchar_t*)fileEntry.nativeFilePath().utf16(),
                             accessRights,
                             shareMode,
                             creationDisp,
                             NULL);
#endif // Q_OS_WINRT

    // Bail out on error.
    if (fileHandle == INVALID_HANDLE_VALUE) {
        q->setError(QFile::OpenError, qt_error_string());
        return false;
    }

    // Truncate the file after successfully opening it if Truncate is passed.
    if (openMode & QIODevice::Truncate)
        q->setSize(0);

    return true;
}