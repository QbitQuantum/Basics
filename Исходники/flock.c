int flock(int fd, int oper) {
    OVERLAPPED o;
    int i = -1;
    HANDLE fh;

    fh = (HANDLE)_get_osfhandle(fd);
    memset(&o, 0, sizeof(o));

    switch(oper) {
		case LOCK_SH:		/* shared lock */
			LK_ERR(LockFileEx(fh, 0, 0, LK_LEN, 0, &o),i);
		break;
		case LOCK_EX:		/* exclusive lock */
			LK_ERR(LockFileEx(fh, LOCKFILE_EXCLUSIVE_LOCK, 0, LK_LEN, 0, &o),i);
		break;
		case LOCK_SH|LOCK_NB:	/* non-blocking shared lock */
			LK_ERR(LockFileEx(fh, LOCKFILE_FAIL_IMMEDIATELY, 0, LK_LEN, 0, &o),i);
		break;
		case LOCK_EX|LOCK_NB:	/* non-blocking exclusive lock */
			LK_ERR(LockFileEx(fh,LOCKFILE_EXCLUSIVE_LOCK|LOCKFILE_FAIL_IMMEDIATELY,0, LK_LEN, 0, &o),i);
		break;
		case LOCK_UN:		/* unlock lock */
			LK_ERR(UnlockFileEx(fh, 0, LK_LEN, 0, &o),i);
		break;
		default:			/* unknown */
			//errno = EINVAL; // i heard that on some versions errno is a function (win32 MT lib?)
		break;
    }
    return i;
}