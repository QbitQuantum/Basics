static int lockfile(int fd) {
	struct flock fl = {.l_type = F_WRLCK, .l_start = 0, .l_whence = SEEK_SET, .l_len = 0};

	return fcntl(fd,F_SETLK, &fl);
}

static int already_running(void) {
	int fd;
	char *buf;

	fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
	if (fd < 0) {
		syslog(LOG_ERR,"can't open %s: %s",LOCKFILE,strerror(errno));
		exit(1);
	}
	if (lockfile(fd) < 0) {
		if (errno == EACCES || errno == EAGAIN) {
			close(fd);
			return 1;
		}
		syslog(LOG_ERR, "can't lock %s: %s",LOCKFILE, strerror(errno));
		exit(1);
	}
	ftruncate(fd,0);
	buf = g_strdup_printf("%ld",(long) getpid());
	write(fd,buf,strlen(buf)+1);
	g_free(buf);
	return 0;
}