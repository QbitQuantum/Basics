void KProcessLock::FreeLock()
{
    BOOL bRetCode = false;
    
    bRetCode = UnlockFile(m_hLockFile, 0, 0, 1, 0);
    KGLOG_PROCESS_ERROR(bRetCode);

    if (m_hLockFile)
    {
        bRetCode = CloseHandle(m_hLockFile);
        KGLOG_PROCESS_ERROR(bRetCode);
        m_hLockFile = INVALID_HANDLE_VALUE;
    }
Exit0:
    return;
}