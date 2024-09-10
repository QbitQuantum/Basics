int
nt_sync(int cdrive)
{
    FD_t drive_fd;
    char sdrive[32];
    int n;

    n = cdrive;
    if (n <= 26) {
	cdrive = 'A' + (n - 1);
    }

    cdrive = _toupper(cdrive);

    (void)sprintf(sdrive, "\\\\.\\%c:", cdrive);
    drive_fd = nt_open(sdrive, O_RDWR, 0666);
    if (drive_fd == INVALID_FD) {
	return -1;
    }

    if (!FlushFileBuffers((HANDLE) drive_fd)) {
	errno = nterr_nt2unix(GetLastError(), EBADF);
	nt_close(drive_fd);
	return -1;
    }
    nt_close(drive_fd);
    return 0;
}