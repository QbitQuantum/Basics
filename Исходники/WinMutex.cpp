bool WinMutex::tryLock()
{
	return TryEnterCriticalSection(&m_mutex) ? true : false;
}