void AttributesAndDateChangerThread::changeTimes(const WinFileInfo& fileInfo) const
{
    // TODO: time changes are not calculated in local time so the shift is not correct
    if(timesNeedChange())
    {
        HANDLE file;
        // Process needs admin rights to succeed here
        if((file = CreateFile(fileInfo.filePath().toStdWString().c_str(),
                              GENERIC_ALL,
                              FILE_SHARE_READ|FILE_SHARE_WRITE,
                              0,
                              OPEN_EXISTING,
                              0,
                              0)) != INVALID_HANDLE_VALUE)
        {
            FILETIME creationTime, lastAccessTime, lastModificationTime;

            WinFileInfo::timetToFileTime(properties_.changeCreationTime_
                                            ? properties_.creationTimestamp_
                                            : fileInfo.creationTime(),
                                         &creationTime);

            WinFileInfo::timetToFileTime(fileInfo.lastAccessTime(), &lastAccessTime);

            if(properties_.shiftModificationTime_)
            {
                time_t newModTime=fileInfo.lastModificationTime()+properties_.modificationTimeShiftInSeconds_;
                WinFileInfo::timetToFileTime(newModTime, &lastModificationTime);
                lastAccessTime=lastModificationTime;
            }
            else
            {
                WinFileInfo::timetToFileTime(properties_.changeLastModificationTime_
                                                ? properties_.lastModificationTimestamp_
                                                : fileInfo.lastModificationTime(),
                                             &lastModificationTime);
                lastAccessTime=lastModificationTime;
            }

            SetFileTime(file, &creationTime, &lastAccessTime, &lastModificationTime);
        }
        CloseHandle(file);
    }
}