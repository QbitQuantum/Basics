static int
alock_share_lock ( int fd, int slot )
{
	int res;

#if defined( HAVE_LOCKF )
	res = 0;	/* lockf has no shared locks */
#elif defined ( HAVE_FCNTL )
	struct flock lock_info;
	(void) memset ((void *) &lock_info, 0, sizeof (struct flock));

	/* The shared lock replaces the existing lock */
	lock_info.l_type = F_RDLCK;
	lock_info.l_whence = SEEK_SET;
	lock_info.l_start = (off_t) (ALOCK_SLOT_SIZE * slot);
	lock_info.l_len = (off_t) ALOCK_SLOT_SIZE;

	res = fcntl (fd, F_SETLK, &lock_info);
#elif defined( _WIN32 )
	HANDLE hh = _get_osfhandle ( fd );
	if (hh == INVALID_HANDLE_VALUE)
		res = -1;
	else {
		OVERLAPPED ov;
		/* Windows locks are mandatory, not advisory.
		 * We must downgrade the lock to allow future
		 * callers to read the slot data.
		 *
		 * First acquire a shared lock. Unlock will
		 * release the existing exclusive lock.
		 */
		ov.hEvent = 0;
		ov.Offset = ALOCK_SLOT_SIZE*slot;
		ov.OffsetHigh = 0;
		if (! LockFileEx (hh, 0, 0, ALOCK_SLOT_SIZE, 0, &ov))
			res = -1;
		if (! UnlockFile (hh, ALOCK_SLOT_SIZE*slot, 0, ALOCK_SLOT_SIZE, 0))
			res = -1;
	}
#else
#   error alock needs lockf, fcntl, or LockFile[Ex]
#endif

	return res;
}