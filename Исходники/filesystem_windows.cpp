    static void CALLBACK completionCallback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
    {
        if(dwErrorCode != ERROR_SUCCESS)
            return;

        if(dwNumberOfBytesTransfered == 0)
            return;

        WatchInfo* watch = reinterpret_cast<WatchInfo*>(lpOverlapped);
        size_t offset = watch->m_bufferOffset;
        PFILE_NOTIFY_INFORMATION notify = nullptr;
        do {
            notify = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(&watch->m_buffer[offset]);
            offset += notify->NextEntryOffset;

            fileos::FileOperation operation = fileos::fileoperation_modified;
            switch(notify->Action)
            {
            case FILE_ACTION_RENAMED_NEW_NAME:
            case FILE_ACTION_ADDED:
                operation = fileos::fileoperation_added;
                break;
            case FILE_ACTION_RENAMED_OLD_NAME:
            case FILE_ACTION_REMOVED:
                operation = fileos::fileoperation_deleted;
                break;
            case FILE_ACTION_MODIFIED:
                operation = fileos::fileoperation_modified;
                break;
            };

            Path filename(notify->FileName, notify->FileNameLength / sizeof(wchar_t));
            FileTime timestamp = getFileTime();

            watch->m_callback(watch->m_id, filename, operation, timestamp);
        } while(notify->NextEntryOffset != 0);

        if(watch->m_isStopping)
            return;

        watch->registerCompletionRoutine(true);
    }