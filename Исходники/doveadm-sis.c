static int
file_contents_equal(const char *path1, const char *path2, ino_t *path2_inode_r)
{
	struct stat st1, st2;
	int fd1, fd2, ret = -1;

	*path2_inode_r = 0;

	/* do a byte-by-byte comparison for the files to find out if they're
	   the same or if this is a hash collision */
	fd1 = open(path1, O_RDONLY);
	if (fd1 == -1) {
		if (errno != ENOENT)
			i_error("open(%s) failed: %m", path1);
		return -1;
	}
	fd2 = open(path2, O_RDONLY);
	if (fd1 == -1) {
		if (errno != ENOENT)
			i_error("open(%s) failed: %m", path2);
		i_close_fd(&fd1);
		return -1;
	}

	if (fstat(fd1, &st1) < 0)
		i_error("fstat(%s) failed: %m", path1);
	else if (fstat(fd2, &st2) < 0)
		i_error("fstat(%s) failed: %m", path1);
	else if (st1.st_size != st2.st_size)
		ret = 0;
	else {
		/* @UNSAFE: sizes match. compare. */
		unsigned char buf1[IO_BLOCK_SIZE], buf2[IO_BLOCK_SIZE];
		ssize_t ret1;
		int ret2;

		while ((ret1 = read(fd1, buf1, sizeof(buf1))) > 0) {
			if ((ret2 = read_full(fd2, buf2, ret1)) <= 0) {
				if (ret2 < 0)
					i_error("read(%s) failed: %m", path2);
				else
					ret = 0;
				break;
			}
			if (memcmp(buf1, buf2, ret1) != 0) {
				ret = 0;
				break;
			}
		}
		if (ret1 < 0)
			i_error("read(%s) failed: %m", path1);
		else if (ret1 == 0)
			ret = 1;
		*path2_inode_r = st2.st_ino;
	}

	if (close(fd1) < 0)
		i_error("close(%s) failed: %m", path1);
	if (close(fd2) < 0)
		i_error("close(%s) failed: %m", path2);

	return ret;
}