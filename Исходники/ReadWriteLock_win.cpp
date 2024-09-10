bool ReadWriteLock::TryBeginRead()
{
	return TryAcquireSRWLockShared(&mLock) == TRUE;
}