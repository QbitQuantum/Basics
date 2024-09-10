void IoBufferPool::unlock()
{
	LeaveCriticalSection(&m_crit);
}