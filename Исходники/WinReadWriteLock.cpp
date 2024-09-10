bool WinReadWriteLock::tryLockForRead()
{
	return TryAcquireSRWLockShared(&m_lock);
}