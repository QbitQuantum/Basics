ssize_t nxffs_write(FAR struct file *filep, FAR const char *buffer, size_t buflen)
{
  FAR struct nxffs_volume_s *volume;
  FAR struct nxffs_wrfile_s *wrfile;
  ssize_t remaining;
  ssize_t nwritten;
  ssize_t total;
  int ret;

  fvdbg("Write %d bytes to offset %d\n", buflen, filep->f_pos);

  /* Sanity checks */

  DEBUGASSERT(filep->f_priv != NULL && filep->f_inode != NULL);

  /* Recover the open file state from the struct file instance */

  wrfile = (FAR struct nxffs_wrfile_s *)filep->f_priv;

  /* Recover the volume state from the open file */

  volume = (FAR struct nxffs_volume_s *)filep->f_inode->i_private;
  DEBUGASSERT(volume != NULL);

  /* Get exclusive access to the volume.  Note that the volume exclsem
   * protects the open file list.
   */

  ret = sem_wait(&volume->exclsem);
  if (ret != OK)
    {
      ret = -get_errno();
      fdbg("ERROR: sem_wait failed: %d\n", ret);
      goto errout;
    }

  /* Check if the file was opened with write access */

  if ((wrfile->ofile.oflags & O_WROK) == 0)
    {
      fdbg("ERROR: File not open for write access\n");
      ret = -EACCES;
      goto errout_with_semaphore;
    }

  /* Loop until we successfully appended all of the data to the file (or an
   * error occurs)
   */

  for (total = 0; total < buflen; )
    {
      remaining = buflen - total;

      /* Have we already allocated the data block? */

      if (wrfile->doffset == 0)
        {
          /* No, allocate the data block now, re-packing if necessary. */

          wrfile->datlen = 0;
          ret = nxffs_wralloc(volume, wrfile, remaining);
          if (ret < 0)
            {
              fdbg("ERROR: Failed to allocate a data block: %d\n", -ret);
              goto errout_with_semaphore;
            }
        }

      /* Seek to the FLASH block containing the data block */

      nxffs_ioseek(volume, wrfile->doffset);

      /* Verify that the FLASH data that was previously written is still intact */

      ret = nxffs_reverify(volume, wrfile);
      if (ret < 0)
        {
          fdbg("ERROR: Failed to verify FLASH data block: %d\n", -ret);
          goto errout_with_semaphore;
        }

      /* Append the data to the end of the data block and write the updated
       * block to flash.
       */

      nwritten = nxffs_wrappend(volume, wrfile, &buffer[total], remaining);
      if (nwritten < 0)
        {
          fdbg("ERROR: Failed to append to FLASH to a data block: %d\n", -ret);
          goto errout_with_semaphore;
        }

      /* Decrement the number of bytes remaining to be written */

      total += nwritten;
    }

  /* Success.. return the number of bytes written */

  ret           = total;
  filep->f_pos  = wrfile->datlen;

errout_with_semaphore:
  sem_post(&volume->exclsem);
errout:
  return ret;
}