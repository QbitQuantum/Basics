void FileChangeWatcher::SetFile(const wxFileName& fileName)
{

    // If the file is in the same directory, we don't need to update anything.
    bool sameDirectory = (fileName.GetPath() == m_fileName.GetPath());

    m_fileName = fileName;
    UpdateFileAttributes();

    if (!sameDirectory || m_handle == NULL)
    {

        if (m_thread != NULL)
        {
            EndThread();
        }

        if (m_handle != NULL)
        {
            FindCloseChangeNotification(m_handle);
            m_handle = NULL;
        }

        m_handle = FindFirstChangeNotification(m_fileName.GetPath(), FALSE, FILE_NOTIFY_CHANGE_ATTRIBUTES);

        // Sometimes the return is NULL and sometimes it's INVALID_HANDLE_VALUE
        // in error conditions.
        if (m_handle == INVALID_HANDLE_VALUE)
        {
            m_handle = NULL;
        }

        if (m_handle != NULL)
        {
            DWORD threadId;
            m_thread = CreateThread(NULL, 0, ThreadProc, this, 0, &threadId);
        }
    
    }

}