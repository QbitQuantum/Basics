/*
 * rm_overwrite --
 *	Overwrite the file 3 times with varying bit patterns.
 *
 * XXX
 * This is a cheap way to *really* delete files.  Note that only regular
 * files are deleted, directories (and therefore names) will remain.
 * Also, this assumes a fixed-block file system (like FFS, or a V7 or a
 * System V file system).  In a logging or COW file system, you'll have to
 * have kernel support.
 */
static int
rm_overwrite(const char *file, struct stat *sbp)
{
	struct stat sb, sb2;
	struct statfs fsb;
	off_t len;
	int bsize, fd, wlen;
	char *buf = NULL;

	fd = -1;
	if (sbp == NULL) {
		if (lstat(file, &sb))
			goto err;
		sbp = &sb;
	}
	if (!S_ISREG(sbp->st_mode))
		return (1);
	if (sbp->st_nlink > 1 && !fflag) {
		warnx("%s (inode %ju): not overwritten due to multiple links",
		    file, (uintmax_t)sbp->st_ino);
		return (0);
	}
	if ((fd = open(file, O_WRONLY|O_NONBLOCK|O_NOFOLLOW, 0)) == -1)
		goto err;
	if (fstat(fd, &sb2))
		goto err;
	if (sb2.st_dev != sbp->st_dev || sb2.st_ino != sbp->st_ino ||
	    !S_ISREG(sb2.st_mode)) {
		errno = EPERM;
		goto err;
	}
	if (fstatfs(fd, &fsb) == -1)
		goto err;
	bsize = MAX(fsb.f_iosize, 1024);
	if ((buf = malloc(bsize)) == NULL)
		err(1, "%s: malloc", file);

#define	PASS(byte) {							\
	memset(buf, byte, bsize);					\
	for (len = sbp->st_size; len > 0; len -= wlen) {		\
		wlen = len < bsize ? len : bsize;			\
		if (write(fd, buf, wlen) != wlen)			\
			goto err;					\
	}								\
}
	PASS(0xff);
	if (fsync(fd) || lseek(fd, (off_t)0, SEEK_SET))
		goto err;
	PASS(0x00);
	if (fsync(fd) || lseek(fd, (off_t)0, SEEK_SET))
		goto err;
	PASS(0xff);
	if (!fsync(fd) && !close(fd)) {
		free(buf);
		return (1);
	}

err:	eval = 1;
	if (buf)
		free(buf);
	if (fd != -1)
		close(fd);
	warn("%s", file);
	return (0);
}