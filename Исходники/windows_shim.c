int
pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
	return (TryAcquireSRWLockShared(&rwlock->rwlock) ? 0 : EBUSY);
}