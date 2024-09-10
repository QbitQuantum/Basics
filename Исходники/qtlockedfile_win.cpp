bool QtLockedFile::lock(LockMode mode, bool block)
{
    if (!isOpen()) {
        qWarning("QtLockedFile::lock(): file is not opened");
        return false;
    }

    if (mode == m_lock_mode)
        return true;

    if (m_lock_mode != 0)
        unlock();

    if (m_semaphore_hnd == 0) {
        QFileInfo fi(*this);
        QString sem_name = QString::fromLatin1(SEMAPHORE_PREFIX)
                           + fi.absoluteFilePath().toLower();

        m_semaphore_hnd = CreateSemaphoreW(0, SEMAPHORE_MAX, SEMAPHORE_MAX,
                                           (TCHAR*)sem_name.utf16());

        if (m_semaphore_hnd == 0) {
            qWarning("QtLockedFile::lock(): CreateSemaphore: %s",
                     errorCodeToString(GetLastError()).toLatin1().constData());
            return false;
        }
    }

    bool gotMutex = false;
    int decrement;
    if (mode == ReadLock) {
        decrement = 1;
    } else {
        decrement = SEMAPHORE_MAX;
        if (m_mutex_hnd == 0) {
            QFileInfo fi(*this);
            QString mut_name = QString::fromLatin1(MUTEX_PREFIX)
                               + fi.absoluteFilePath().toLower();

            m_mutex_hnd = CreateMutexW(NULL, FALSE, (TCHAR*)mut_name.utf16());

            if (m_mutex_hnd == 0) {
                qWarning("QtLockedFile::lock(): CreateMutex: %s",
                         errorCodeToString(GetLastError()).toLatin1().constData());
                return false;
            }
        }
        DWORD res = WaitForSingleObject(m_mutex_hnd, block ? INFINITE : 0);
        if (res == WAIT_TIMEOUT)
            return false;
        if (res == WAIT_FAILED) {
            qWarning("QtLockedFile::lock(): WaitForSingleObject (mutex): %s",
                     errorCodeToString(GetLastError()).toLatin1().constData());
            return false;
        }
        gotMutex = true;
    }

    for (int i = 0; i < decrement; ++i) {
        DWORD res = WaitForSingleObject(m_semaphore_hnd, block ? INFINITE : 0);
        if (res == WAIT_TIMEOUT) {
            if (i) {
                // A failed nonblocking rw locking. Undo changes to semaphore.
                if (ReleaseSemaphore(m_semaphore_hnd, i, NULL) == 0) {
                    qWarning("QtLockedFile::unlock(): ReleaseSemaphore: %s",
                             errorCodeToString(GetLastError()).toLatin1().constData());
                    // Fall through
                }
            }
            if (gotMutex)
                ReleaseMutex(m_mutex_hnd);
            return false;
	}
        if (res != WAIT_OBJECT_0) {
            if (gotMutex)
                ReleaseMutex(m_mutex_hnd);
            qWarning("QtLockedFile::lock(): WaitForSingleObject (semaphore): %s",
                        errorCodeToString(GetLastError()).toLatin1().constData());
            return false;
        }
    }

    m_lock_mode = mode;
    if (gotMutex)
        ReleaseMutex(m_mutex_hnd);
    return true;
}