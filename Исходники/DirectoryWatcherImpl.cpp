    void DirectoryWatcherImpl::watch()
    {
        m_fileHandle = CreateFileA(m_directory.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
            
        if (m_fileHandle == INVALID_HANDLE_VALUE)
        {
            JOP_DEBUG_ERROR("Failed to start directory watcher, directory: " << m_directory);
            m_active = false;
            m_error = true;
            m_fileHandle = nullptr;
            return;
        }
    
        FILE_NOTIFY_INFORMATION fileNotifyInfo[4];
        DWORD bytesReturned = sizeof(FILE_NOTIFY_INFORMATION);
    
        while (!m_shouldClose)
        {
            while (!m_active)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
    
            if (ReadDirectoryChangesW(m_fileHandle,
                &fileNotifyInfo,
                sizeof(fileNotifyInfo),
                TRUE,
                FILE_NOTIFY_CHANGE_LAST_WRITE,
                &bytesReturned,
                NULL,
                NULL))
            {
                if (fileNotifyInfo[0].Action == FILE_ACTION_MODIFIED)
                {
                    DirectoryWatcher::Info info;
    
                    info.filename = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::wstring(fileNotifyInfo[0].FileName, fileNotifyInfo[0].FileNameLength / sizeof(wchar_t)));
    
                    if (!(info == m_lastEvent))
                    {
                        m_lastEvent = info;

                        m_callback(m_lastEvent);
                    }
                }
            }
        }
    }