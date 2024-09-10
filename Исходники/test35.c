void test35a()
{				/* Test normal operation. */
  struct stat st;
  struct utimbuf ub;
  time_t time1, time2;
  int cnt;

  subtest = 1;

  /* Creat scratch file. */
  Creat("foo");

  /* Set file times back two seconds. */
  Stat("foo", &st);
  ub.actime = st.st_atime - 2;
  ub.modtime = st.st_mtime - 2;
  Time(&time1);
  utime("foo", &ub);
  Time(&time2);
  Stat("foo", &st);
  if (ub.actime != st.st_atime) e(1);
  if (ub.modtime != st.st_mtime) e(2);

  /* The status changed time sould be changed. */
#ifndef V1_FILESYSTEM
  if (st.st_ctime < time1) e(3);
#endif
  if (st.st_ctime > time2) e(4);

  /* Add twenty seconds. */
  Stat("foo", &st);
  ub.actime = st.st_atime + 20;
  ub.modtime = st.st_mtime + 20;
  Time(&time1);
  utime("foo", &ub);
  Time(&time2);
  Stat("foo", &st);
  if (ub.actime != st.st_atime) e(5);
  if (ub.modtime != st.st_mtime) e(6);
  if (st.st_ctime < time1) e(7);
#ifndef V1_FILESYSTEM
  if (st.st_ctime > time2) e(8);
#endif

  /* Try 100 times to do utime in less than one second. */
  cnt = 0;
  do {
	Time(&time1);
	utime("foo", (struct utimbuf *) NULL);
	Time(&time2);
  } while (time1 != time2 && cnt++ < 100);
  if (time1 == time2) {
	Stat("foo", &st);
	Time(&time2);
	if (st.st_atime != time1) e(9);
	if (st.st_mtime != time1) e(10);
  } else {
	Stat("foo", &st);
	if (st.st_atime > time2) e(11);
	if (st.st_mtime > time2) e(12);
	Time(&time2);
	if (st.st_atime < time1) e(13);
	if (st.st_mtime < time1) e(14);
  }
  if (st.st_ctime < time1) e(15);
  if (st.st_ctime > time2) e(16);

  System("rm -rf ../DIR_35/*");
}