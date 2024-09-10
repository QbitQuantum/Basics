static inline int dolock(xc_fcntl_mutex_t *fcntl_mutex, int type)
{
	static OVERLAPPED offset = {0, 0, 0, 0, NULL};

	if (type == LCK_UN) {
		return UnlockFileEx(fcntl_mutex->fd, 0, 1, 0, &offset);
	}
	else {
		return LockFileEx(fcntl_mutex->fd, type, 0, 1, 0, &offset);
	}
}