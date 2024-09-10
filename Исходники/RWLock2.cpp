void CRWLock2::EnterRead() {
    t_procId = GetCurrentProcessorNumber();
    AcquireSRWLockShared(&m_lock[t_procId]);
}