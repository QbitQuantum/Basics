void ThreadGate::Open(void)
{
#if defined(OVR_CAPTURE_POSIX)
    pthread_mutex_lock(&m_mutex);
    m_open = true;
    pthread_cond_broadcast(&m_cond);
    pthread_mutex_unlock(&m_mutex);
#elif defined(OVR_CAPTURE_WINDOWS)
    EnterCriticalSection(&m_cs);
    m_open = true;
    WakeAllConditionVariable(&m_cond);
    LeaveCriticalSection(&m_cs);
#endif
}