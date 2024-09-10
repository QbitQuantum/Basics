inline void WinThreadCVImpl::wakeOne ()
{
    m_mutex.lock();
    m_wakeups = CWT_MIN(m_wakeups + 1, m_waiters);
    WakeConditionVariable(& m_cond);
    m_mutex.unlock();
}