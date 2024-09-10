void test_dup2(const struct socket_test_info *info)
{
	struct stat info1;
	struct stat info2;
	int sd;
	int fd;
	int rc;
	int on;

	debug("entering test_dup2()");
	info->callback_cleanup();

	SOCKET(sd, info->domain, info->type, 0);

	on = 1;
	(void)setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	rc = bind(sd, info->serveraddr, info->serveraddrlen);
	if (rc != 0) {
		test_fail("bind() should have worked");
	}

	fd = open("/dev/null", O_RDONLY);
	if (fd == -1) {
		test_fail("open(\"/dev/null\", O_RDONLY) failed");
	}

	fd = dup2(sd, fd);
	if (fd == -1) {
		test_fail("dup2(sd, fd) failed.");
	}

	memset(&info1, '\0', sizeof(struct stat));
	memset(&info2, '\0', sizeof(struct stat));

	rc = fstat(fd, &info1);
	if (rc == -1) {
		test_fail("fstat(fd, &info1) failed");
	}

	rc = fstat(sd, &info2);
	if (rc == -1) {
		test_fail("fstat(sd, &info2) failed");
	}

	if (!(info1.st_ino == info2.st_ino &&
		major(info1.st_dev) == major(info2.st_dev) &&
		minor(info1.st_dev) == minor(info2.st_dev))) {

		test_fail("dup2() failed");
	}

	CLOSE(fd);
	CLOSE(sd);

	info->callback_cleanup();
	debug("leaving test_dup2()");

}