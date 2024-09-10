static int zend_file_cache_flock(int fd, int op)
{
	OVERLAPPED offset = {0,0,0,0,NULL};
	if (op == LOCK_EX) {
		if (LockFileEx((HANDLE)_get_osfhandle(fd),
		               LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &offset) == TRUE) {
			return 0;
		}
	} else if (op == LOCK_SH) {
		if (LockFileEx((HANDLE)_get_osfhandle(fd),
		               0, 0, 1, 0, &offset) == TRUE) {
			return 0;
		}
	} else if (op == LOCK_UN) {
		if (UnlockFileEx((HANDLE)_get_osfhandle(fd),
		                 0, 1, 0, &offset) == TRUE) {
			return 0;
		}
	}
	return -1;
}