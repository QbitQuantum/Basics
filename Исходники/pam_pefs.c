static int
flopen_retry(const char *filename)
{
	int fd, try;

	for (try = 1; try <= 1024; try *= 2) {
		fd = flopen(filename, PEFS_SESSION_FILE_FLAGS,
		    PEFS_SESSION_FILE_MODE);
		if (fd != -1)
			return (fd);
		else if (errno != EWOULDBLOCK)
			return (-1);
		// Exponential back-off up to 1 second
		usleep(try * 1000000 / 1024);
	}
	errno = ETIMEDOUT;
	return (-1);
}

static int
pefs_session_count_incr(const char *user, bool incr)
{
	struct stat sb;
	struct timespec tp_uptime, tp_now;
	ssize_t offset;
	int fd, total = 0;
	char filename[MAXPATHLEN], buf[16];
	const char *errstr;

	snprintf(filename, sizeof(filename), "%s/%s", PEFS_SESSION_DIR, user);

	if (lstat(PEFS_SESSION_DIR, &sb) == -1) {
		if (errno != ENOENT) {
			pefs_warn("unable to access session directory %s: %s",
			    PEFS_SESSION_DIR, strerror(errno));
			return (-1);
		}
		if (mkdir(PEFS_SESSION_DIR, PEFS_SESSION_DIR_MODE) == -1) {
			pefs_warn("unable to create session directory %s: %s",
			    PEFS_SESSION_DIR, strerror(errno));
			return (-1);
		}
	} else if (!S_ISDIR(sb.st_mode)) {
		pefs_warn("%s is not a directory", PEFS_SESSION_DIR);
		return (-1);
	}

	if ((fd = flopen_retry(filename)) == -1) {
		pefs_warn("unable to create session counter file %s: %s",
		    filename, strerror(errno));
		return (-1);
	}

	if ((offset = pread(fd, buf, sizeof(buf) - 1, 0)) == -1) {
		pefs_warn("unable to read from the session counter file %s: %s",
		    filename, strerror(errno));
		close(fd);
		return (-1);
	}
	buf[offset] = '\0';
	if (offset != 0) {
		total = strtonum(buf, 0, INT_MAX, &errstr);
		if (errstr != NULL)
			pefs_warn("corrupted session counter file: %s: %s",
			    filename, errstr);
	}

	/*
	 * Determine if this is the first increment of the session file.
	 *
	 * It is considered the first increment if the session file has not
	 * been modified since the last boot time.
	 */
	if (incr && total > 0) {
		if (fstat(fd, &sb) == -1) {
			pefs_warn("unable to access session counter file %s: %s",
			    filename, strerror(errno));
			close(fd);
			return (-1);
		}
		/*
		 * Check is messy and will fail if wall clock isn't monotonical
		 * (e.g. because of ntp, DST, leap seconds)
		 */
		clock_gettime(CLOCK_REALTIME_FAST, &tp_now);
		clock_gettime(CLOCK_UPTIME_FAST, &tp_uptime);
		if (sb.st_mtime < tp_now.tv_sec - tp_uptime.tv_sec) {
			pefs_warn("stale session counter file: %s",
			    filename);
			total = 0;
		}
	}

	lseek(fd, 0L, SEEK_SET);
	ftruncate(fd, 0L);

	total += incr ? 1 : -1;
	if (total < 0) {
		pefs_warn("corrupted session counter file: %s",
		    filename);
		total = 0;
	} else
		pefs_warn("%s: session count %d", user, total);

	buf[0] = '\0';
	snprintf(buf, sizeof(buf), "%d", total);
	pwrite(fd, buf, strlen(buf), 0);
	close(fd);

	return (total);
}

static int
pam_pefs_checkfs(const char *homedir)
{
	char fsroot[MAXPATHLEN];
	int error;

	error = pefs_getfsroot(homedir, 0, fsroot, sizeof(fsroot));
	if (error != 0) {
		pefs_warn("file system is not mounted: %s", homedir);
		return (PAM_USER_UNKNOWN);
	} if (strcmp(fsroot, homedir) != 0) {
		pefs_warn("file system is not mounted on home dir: %s", fsroot);
		return (PAM_USER_UNKNOWN);
	}

	return (PAM_SUCCESS);
}