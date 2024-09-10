int
pgut_flock(int fd, int operation)
{
	BOOL	ret;
	HANDLE	handle = (HANDLE) _get_osfhandle(fd);
	DWORD	lo = 0;
	DWORD	hi = 0;

	if (operation & LOCK_UN)
	{
		ret = UnlockFileEx(handle, 0, lo, hi, NULL);
	}
	else
	{
		DWORD	flags = 0;
		if (operation & LOCK_EX)
			flags |= LOCKFILE_EXCLUSIVE_LOCK;
		if (operation & LOCK_NB)
			flags |= LOCKFILE_FAIL_IMMEDIATELY;
		ret = LockFileEx(handle, flags, 0, lo, hi, NULL);
	}

	if (!ret)
	{
		_dosmaperr(GetLastError());
		return -1;
	}

	return 0;
}