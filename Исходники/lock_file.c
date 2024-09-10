int tup_unflock(tup_lock_t fd)
{
	if(UnlockFile(fd, 0, 0, 1, 0) == 0) {
		errno = EIO;
		return -1;
	}
	return 0;
}