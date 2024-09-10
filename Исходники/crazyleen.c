int
already_running(const char *fpathname)
{
	int		fd;
	char	buf[16];
	
	fd = open(fpathname, O_RDWR|O_CREAT, LOCKMODE);
	if (fd < 0) {
		syslog(LOG_ERR, "can't open %s: %s", fpathname, strerror(errno));
		exit(1);
	}
	if (lockfile(fd) < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			close(fd);
			return(1);
		}
		syslog(LOG_ERR, "can't lock %s: %s", fpathname, strerror(errno));
		exit(1);
	}

	//cut file length to 0.
	ftruncate(fd, 0);	
	
	//write pid to file.
	sprintf(buf, "%ld", (long)getpid());
	write(fd, buf, strlen(buf)+1);	
	return(0);
}