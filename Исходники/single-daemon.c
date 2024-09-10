int already_running(void)
{
	int fd;
	char buf[16];

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if(fd < 0) {
		syslog(LOG_ERR, "can't open %s : %s", LOCKFILE, strerror(errno));
		exit(1);
	}

	if(lockfile(fd) < 0) {
		if(errno == EACCES || errno == EAGAIN) {
			close(fd);
			return(1);
		}

		syslog(LOG_ERR, "can't lock %s : %s", LOCKFILE, strerror(errno));
		exit(1);
	}

	/*
	 * Truncate the file so that when you write out the buffer, nothing that
	 * was longer than the buffer is still left in the file.
	 */
	ftruncate(fd, 0);
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf) + 1);
	return(0);
}