void setup_every_copy()
{
	int i;
	char tmpfilename[256] = "";

	/* Initialize test dir and file names */
	sprintf(pathname, "readlinkattestdir%d", getpid());
	sprintf(dpathname, "dreadlinkattestdir%d", getpid());
	sprintf(testfile, "readlinkattestfile%d.txt", getpid());
	sprintf(dtestfile, "dreadlinkattestfile%d.txt", getpid());
	sprintf(testfile2, "readlinkattestdir%d/readlinkattestfile%d.txt",
		getpid(), getpid());
	sprintf(dtestfile2, "dreadlinkattestdir%d/dreadlinkattestfile%d.txt",
		getpid(), getpid());
	sprintf(testfile3, "/tmp/readlinkattestfile%d.txt", getpid());
	sprintf(dtestfile3, "/tmp/dreadlinkattestfile%d.txt", getpid());

	ret = mkdir(pathname, 0700);
	if (ret < 0) {
		perror("mkdir: ");
		exit(-1);
	}

	ret = mkdir(dpathname, 0700);
	if (ret < 0) {
		perror("mkdir: ");
		exit(-1);
	}

	dirfd = open(dpathname, O_DIRECTORY);
	if (dirfd < 0) {
		perror("open: ");
		exit(-1);
	}

	fd = open(testfile, O_CREAT | O_RDWR, 0600);
	if (fd < 0) {
		perror("open: ");
		exit(-1);
	}

	ret = symlink(testfile, dtestfile);
	if (ret < 0) {
		perror("symlink: ");
		exit(-1);
	}

	fd = open(testfile2, O_CREAT | O_RDWR, 0600);
	if (fd < 0) {
		perror("open: ");
		exit(-1);
	}

	tmpfilename[0] = '\0';
	strcat(strcat(tmpfilename, "../"), testfile2);
	ret = symlink(tmpfilename, dtestfile2);
	if (ret < 0) {
		perror("symlink: ");
		exit(-1);
	}

	fd = open(testfile3, O_CREAT | O_RDWR, 0600);
	if (fd < 0) {
		perror("open: ");
		exit(-1);
	}

	ret = symlink(testfile3, dtestfile3);
	if (ret < 0) {
		perror("symlink: ");
		exit(-1);
	}

	fds[0] = fds[1] = dirfd;
	fds[2] = fd;
	fds[3] = 100;
	fds[4] = AT_FDCWD;

	filenames[0] = filenames[2] = filenames[3] = filenames[4] = dtestfile;
	filenames[1] = dtestfile3;

	for (i = 0; i < TEST_CASES; i++)
		expected_buff[i][0] = '\0';

	strcat(strcat(expected_buff[0], "../"), testfile2);
	strcat(expected_buff[1], testfile3);
	strcat(expected_buff[2], "");
	strcat(expected_buff[3], "");
	strcat(expected_buff[4], testfile);
}