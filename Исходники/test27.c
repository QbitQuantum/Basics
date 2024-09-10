void test27c()
{				/* Test error response. */
  struct stat st;
  int fd, i;

  subtest = 3;

  System("echo Hi > foo");	/* Make a file called foo. */
  /* Check if a un searchable dir is handled ok. */
  Chdir("..");			/* cd .. */
  System("chmod 677 DIR_27");	/* no search permission */
  if (stat("DIR_27/nono", &st) != -1) e(1);
  if (superuser) {
	if (errno != ENOENT) e(2);	/* su has access */
  }
  if (!superuser) {
	if (errno != EACCES) e(3);	/* we don't ;-) */
  }
  System("chmod 777 DIR_27");
  Chdir("DIR_27");		/* back to test dir */

  /* Check on ToLongName etc. */
#ifdef _POSIX_NO_TRUNC
# if _POSIX_NO_TRUNC - 0 != -1
  if (stat(ToLongName, &st) != -1) e(4);	/* name is too long */
  if (errno != ENAMETOOLONG) e(5);
# endif
#else
# include "error, this case requires dynamic checks and is not handled"
#endif
  if (stat(ToLongPath, &st) != -1) e(6);	/* path is too long */
  if (errno != ENAMETOOLONG) e(7);

  /* Test some common errors. */
  if (stat("nono", &st) != -1) e(8);	/* nono nonexistent */
  if (errno != ENOENT) e(9);
  if (stat("", &st) != -1) e(10);	/* try empty */
  if (errno != ENOENT) e(11);
  if (stat("foo/bar", &st) != -1) e(12);	/* foo is a file */
  if (errno != ENOTDIR) e(13);

  /* Test fstat on file descriptors that are not open. */
  for (i = 3; i < 6; i++) {
	if (fstat(i, &st) != -1) e(14);
	if (errno != EBADF) e(15);
  }

  /* Test if a just closed file is `fstat()'-able. */
  if ((fd = open("foo", O_RDONLY)) != 3) e(16);	/* open foo */
  if (fstat(fd, &st) != 0) e(17);	/* get stat */
  if (close(fd) != 0) e(18);	/* close it */
  if (fstat(fd, &st) != -1) e(19);	/* get stat */
  if (errno != EBADF) e(20);
  System("rm -rf ../DIR_27/*");
}