void rwlock_rdunlock(rwlock_t *l)
{
#ifndef _WIN32
	atomic_ref(&l->s.write);
#else
	ReleaseSRWLockShared(l);
#endif
}