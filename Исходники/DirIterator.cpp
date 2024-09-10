void TDirIterator::start()
{
    Q_ASSERT(m_Status == stNotStarted);

    #ifdef Q_OS_WIN
        QString Path = PathToLongWinPath(m_StartPath);
        if (!Path.endsWith(QDir::separator()))
            Path += QDir::separator();
        Path += '*';

        m_hFind = FindFirstFileExW((LPCWSTR)Path.utf16(),
                                   FindExInfoStandard,
                                   &m_FindData,
                                   FindExSearchNameMatch,
                                   NULL,
                                   0);
        if (m_hFind != INVALID_HANDLE_VALUE) {
            m_FileInfoEx.m_Data->init(m_StartPath, &m_FindData);
            m_Status = stStarted;
        }
        else {
            DWORD ErrCode = GetLastError();
            if (ErrCode != ERROR_FILE_NOT_FOUND) {
                qWarning("TDirIterator::start. FindFirstFileEx error on \"%s\": %s",
                         qPrintable(m_StartPath),
                         qPrintable(GetSystemErrorString(ErrCode)));
            }
            m_Status = stFinished;
        }
    #else
        m_pDir = ::opendir(m_StartPath.toLocal8Bit().data());
        if (m_pDir != NULL) {
            m_Status = stStarted;
            getNext();
        }
        else {
            qWarning("TDirIterator::start. opendir error on \"%s\": %s",
                     qPrintable(m_StartPath),
                     qPrintable(GetSystemErrorString()));
            m_Status = stFinished;
        }
    #endif

    if (m_FileInfoEx.exists()) {
        if (!m_FileInfoEx.isDir()) {
            qWarning("TDirIterator::start. Not folder: \"%s\".",
                     qPrintable(m_StartPath));
            finish();
        }
    }
    else {
        qWarning("TDirIterator::start. Object not exists or insufficient privileges: \"%s\".",
                 qPrintable(m_StartPath));
    }
}