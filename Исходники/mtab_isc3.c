static
lockmnttab(void)
{
  if (mtlckf == 0) {		/* need lock on /etc/.mnt.lock */
    mtlckf = open(mtlckname, O_RDWR);
    if (mtlckf >= 0) {
      if (lockfile(mtlckf, F_WRLCK) < 0) {
	close(mtlckf);
	mtlckf = 0;
#ifdef DEBUG
	dlog("lock failed %m");
#endif /* DEBUG */
      } else {
	return 0;
      }
    }
  }
  plog(XLOG_ERROR, "Unable to lock %s: %m", mtlckname);
  return -1;
}