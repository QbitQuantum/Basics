void OriginLock::unlock()
{
#if USE(FILE_LOCK)
    // If the file descriptor was uninitialized, then that means the directory
    // containing the lock has been deleted before we opened the lock file, or
    // we were given a path to a non-existant directory. Which, in turn, means
    // that there's nothing to unlock.
    if (m_lockHandle == invalidPlatformFileHandle) 
        return;

    unlockFile(m_lockHandle);

    closeFile(m_lockHandle);
    m_lockHandle = invalidPlatformFileHandle;
#endif

    m_mutex.unlock();
}