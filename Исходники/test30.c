void test30c()
{
  int fd, does_truncate;

  subtest = 3;

  System("rm -rf ../DIR_30/*");

  if (!superuser) {
	/* Test if creat is not usable to open files with the wrong mode */
	System("> nono; chmod 177 nono");
	fd = creat("nono", 0777);
	if (fd != -1) e(1);
	if (errno != EACCES) e(2);
  }
  if (mkdir("bar", 0777) != 0) e(3);	/* make bar */

  /* Check if no access on part of path generates the correct error. */
  System("chmod 577 bar");	/* r-xrwxrwx */
  if (!superuser) {
	/* Normal users can't creat without write permision. */
	if (creat("bar/nono", 0666) != -1) e(4);
	if (errno != EACCES) e(5);
	if (creat("bar/../nono", 0666) != -1) e(6);
	if (errno != EACCES) e(7);
  }
  if (superuser) {
	/* Super user can still creat stuff. */
	if ((fd = creat("bar/nono", 0666)) != 3) e(8);
	if (close(fd) != 0) e(9);
	if (unlink("bar/nono") != 0) e(10);
  }

  /* Clean up bar. */
  System("rm -rf bar");

  /* Test ToLongName and ToLongPath */
  does_truncate = does_fs_truncate();
  fd = creat(ToLongName, 0777);
  if (does_truncate) {
	if (fd == -1) e(11);
	if (close(fd) != 0) e(12);
  } else {
	if (fd != -1) e(13);
	if (errno != ENAMETOOLONG) e(14);
	(void) close(fd);			/* Just in case. */
  }

  ToLongPath[PATH_MAX - 2] = '/';
  ToLongPath[PATH_MAX - 1] = 'a';
  if ((fd = creat(ToLongPath, 0777)) != -1) e(15);
  if (errno != ENAMETOOLONG) e(16);
  if (close(fd) != -1) e(17);
  ToLongPath[PATH_MAX - 1] = '/';
}