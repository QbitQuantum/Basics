QDateTime AssetCache::LastModified(const QString &assetRef)
{
    QString absolutePath = FindInCache(assetRef);
    if (absolutePath.isEmpty())
        return QDateTime();

#ifdef Q_WS_WIN
    HANDLE fileHandle = (HANDLE)OpenFileHandle(absolutePath);
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        LogError("AssetCache: Failed to open cache file to read last modified time: " + assetRef);
        return QDateTime();
    }

    // Get last write time.
    FILETIME fileTime;
    BOOL success = GetFileTime(fileHandle, 0, 0, &fileTime); // http://msdn.microsoft.com/en-us/library/windows/desktop/ms724320(v=VS.85).aspx
    CloseHandle(fileHandle);
    if (!success)
    {
        LogError("AssetCache: Failed to read cache file last modified time: " + assetRef);
        return QDateTime();
    }

    // Convert to UTC.
    SYSTEMTIME sysTime;
    if (!FileTimeToSystemTime(&fileTime, &sysTime)) // http://msdn.microsoft.com/en-us/library/windows/desktop/ms724280(v=VS.85).aspx
    {
        LogError("Win32 FileTimeToSystemTime failed for asset ref " + assetRef);
        return QDateTime();
    }

    // Ignore msec
    QDateTime dateTime;
    dateTime.setTimeSpec(Qt::UTC);
    dateTime.setDate(QDate((int)sysTime.wYear, (int)sysTime.wMonth, (int)sysTime.wDay));
    dateTime.setTime(QTime((int)sysTime.wHour, (int)sysTime.wMinute, (int)sysTime.wSecond, 0));
    return dateTime;
#else
    QDateTime dateTime;
    QString nativePath = QDir::toNativeSeparators(absolutePath);
    struct stat fileStats;
    if (stat(nativePath.toStdString().c_str(), &fileStats) == 0)
    {
        qint64 msecFromEpoch = (qint64)fileStats.st_mtime * 1000;
        dateTime.setMSecsSinceEpoch(msecFromEpoch);
    }
    else
        LogError("AssetCache: Failed to read cache file last modified time: " + assetRef);
    return dateTime;
#endif
}