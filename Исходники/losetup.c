int losetup(FAR const char *devname, FAR const char *filename,
            uint16_t sectsize, off_t offset, bool readonly)
{
  FAR struct loop_struct_s *dev;
  struct stat sb;
  int ret;

  /* Sanity check */

#ifdef CONFIG_DEBUG
  if (!devname || !filename || !sectsize)
    {
      return -EINVAL;
    }
#endif

  /* Get the size of the file */

  ret = stat(filename, &sb);
  if (ret < 0)
    {
      dbg("Failed to stat %s: %d\n", filename, get_errno());
      return -get_errno();
    }

  /* Check if the file system is big enough for one block */

  if (sb.st_size - offset < sectsize)
    {
      dbg("File is too small for blocksize\n");
      return -ERANGE;
    }

  /* Allocate a loop device structure */

  dev = (FAR struct loop_struct_s *)kmm_zalloc(sizeof(struct loop_struct_s));
  if (!dev)
    {
      return -ENOMEM;
    }

  /* Initialize the loop device structure. */

  sem_init(&dev->sem, 0, 1);
  dev->nsectors  = (sb.st_size - offset) / sectsize;
  dev->sectsize  = sectsize;
  dev->offset    = offset;

  /* Open the file. */

#ifdef CONFIG_FS_WRITABLE
  dev->writeenabled = false; /* Assume failure */
  dev->fd           = -1;

  /* First try to open the device R/W access (unless we are asked
   * to open it readonly).
   */

  if (!readonly)
    {
      dev->fd = open(filename, O_RDWR);
    }

  if (dev->fd >= 0)
    {
      dev->writeenabled = true; /* Success */
    }
  else
#endif
    {
      /* If that fails, then try to open the device read-only */

      dev->fd = open(filename, O_RDWR);
      if (dev->fd < 0)
        {
          dbg("Failed to open %s: %d\n", filename, get_errno());
          ret = -get_errno();
          goto errout_with_dev;
        }
    }

  /* Inode private data will be reference to the loop device structure */

  ret = register_blockdriver(devname, &g_bops, 0, dev);
  if (ret < 0)
    {
      fdbg("register_blockdriver failed: %d\n", -ret);
      goto errout_with_fd;
    }

  return OK;

errout_with_fd:
  close(dev->fd);
errout_with_dev:
  kmm_free(dev);
  return ret;
}