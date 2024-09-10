Mutex::~Mutex()
{
    DeleteCriticalSection(&m_mutex.m_internalMutex);
}