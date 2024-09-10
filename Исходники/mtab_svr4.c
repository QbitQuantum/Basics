/* return 0 if locking succeeded, -1 if failed */
static int
lockmnttab(void)
{
#ifdef MOUNT_TABLE_ON_FILE
  /* if mnttab file is locked, all is well */
  if (mntent_lock_fd >= 0)
    return 0;

  /* need to lock mnttab file. first, open the file */
  mntent_lock_fd = open(mtlckname, O_RDWR | O_CREAT, 0600);
  if (mntent_lock_fd < 0) {
    plog(XLOG_ERROR, "Unable to open/creat %s: %m", mtlckname);
    return -1;
  }

  /* if succeeded in opening the file, try to lock it */
  if (lockfile(mntent_lock_fd, F_WRLCK) < 0) {
    close(mntent_lock_fd);
    mntent_lock_fd = -1;
#ifdef DEBUG
    dlog("lock %s failed: %m", mtlckname);
#endif /* DEBUG */
    return -1;
  }
#else /* not MOUNT_TABLE_ON_FILE */
  /* fake lock for in-kernel mount table */
#endif /* not MOUNT_TABLE_ON_FILE */

  /* finally, succeeded in also locking the file */
  return 0;
}