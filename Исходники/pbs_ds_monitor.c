static int
lock_out(HANDLE hFile , int op)
{
	DWORD dwNumBytesWritten;
	BOOL fSuccess;
	OVERLAPPED sOverlapped;
	char buf[PBS_MAXHOSTNAME + 10];

	if (op == F_WRLCK) {
		sOverlapped.Offset = 0;
		sOverlapped.OffsetHigh = 100;
		sOverlapped.hEvent = 0;

		fSuccess = LockFileEx(hFile,
			LOCKFILE_EXCLUSIVE_LOCK |
			LOCKFILE_FAIL_IMMEDIATELY,
			0, 0, 1000, &sOverlapped);
		if (fSuccess) {
			/* if write-lock, record hostname and pid in file */
			(void) sprintf(buf, "%s:%d\n", thishost, getpid());
			fSuccess = WriteFile(hFile,
				buf,
				strlen(buf),
				&dwNumBytesWritten,
				NULL);
			return 0;
		}
	} else {
		/* unlock and return */
		fSuccess = UnlockFileEx(hFile, 0, 0, 1000, &sOverlapped);
		if (fSuccess)
			return 0;
	}
	return 1;
}