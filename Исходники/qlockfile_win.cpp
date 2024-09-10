QT_BEGIN_NAMESPACE

QLockFile::LockError QLockFilePrivate::tryLock_sys()
{
    const QFileSystemEntry fileEntry(fileName);
    // When writing, allow others to read.
    // When reading, QFile will allow others to read and write, all good.
    // Adding FILE_SHARE_DELETE would allow forceful deletion of stale files,
    // but Windows doesn't allow recreating it while this handle is open anyway,
    // so this would only create confusion (can't lock, but no lock file to read from).
    const DWORD dwShareMode = FILE_SHARE_READ;
#ifndef Q_OS_WINRT
    SECURITY_ATTRIBUTES securityAtts = { sizeof(SECURITY_ATTRIBUTES), NULL, FALSE };
    HANDLE fh = CreateFile((const wchar_t*)fileEntry.nativeFilePath().utf16(),
                           GENERIC_WRITE,
                           dwShareMode,
                           &securityAtts,
                           CREATE_NEW, // error if already exists
                           FILE_ATTRIBUTE_NORMAL,
                           NULL);
#else // !Q_OS_WINRT
    HANDLE fh = CreateFile2((const wchar_t*)fileEntry.nativeFilePath().utf16(),
                            GENERIC_WRITE,
                            dwShareMode,
                            CREATE_NEW, // error if already exists
                            NULL);
#endif // Q_OS_WINRT
    if (fh == INVALID_HANDLE_VALUE) {
        const DWORD lastError = GetLastError();
        switch (lastError) {
        case ERROR_SHARING_VIOLATION:
        case ERROR_ALREADY_EXISTS:
        case ERROR_FILE_EXISTS:
        case ERROR_ACCESS_DENIED: // readonly file, or file still in use by another process. Assume the latter, since we don't create it readonly.
            return QLockFile::LockFailedError;
        default:
            qWarning() << "Got unexpected locking error" << lastError;
            return QLockFile::UnknownError;
        }
    }

    // We hold the lock, continue.
    fileHandle = fh;
    // Assemble data, to write in a single call to write
    // (otherwise we'd have to check every write call)
    QByteArray fileData;
    fileData += QByteArray::number(QCoreApplication::applicationPid());
    fileData += '\n';
    fileData += qAppName().toUtf8();
    fileData += '\n';
    //fileData += localHostname(); // gethostname requires winsock init, see QHostInfo...
    fileData += '\n';
    DWORD bytesWritten = 0;
    QLockFile::LockError error = QLockFile::NoError;
    if (!WriteFile(fh, fileData.constData(), fileData.size(), &bytesWritten, NULL) || !FlushFileBuffers(fh))
        error = QLockFile::UnknownError; // partition full
    return error;
}