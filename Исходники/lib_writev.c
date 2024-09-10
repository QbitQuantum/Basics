ssize_t writev(int fildes, FAR const struct iovec *iov, int iovcnt)
{
  ssize_t ntotal;
  ssize_t nwritten;
  size_t remaining;
  FAR uint8_t *buffer;
  off_t pos;
  int i;

  /* Get the current file position in case we have to reset it */

  pos = lseek(fildes, 0, SEEK_CUR);
  if (pos == (off_t)-1)
    {
      return ERROR;
    }

  /* Process each entry in the struct iovec array */

  for (i = 0, ntotal = 0; i < iovcnt; i++)
    {
      /* Ignore zero-length writes */

      if (iov[i].iov_len > 0)
        {
          buffer    = iov[i].iov_base;
          remaining = iov[i].iov_len;

          /* Write repeatedly as necessary to write the entire buffer */

          do
            {
              /* NOTE:  write() is a cancellation point */

              nwritten = write(fildes, buffer, remaining);

              /* Check for a write error */

              if (nwritten < 0)
                {
                  /* Save the errno value */

                  int save = get_errno();

                  /* Restore the file position */

                  (void)lseek(fildes, pos, SEEK_SET);

                  /* Restore the errno value */

                  set_errno(save);
                  return ERROR;
                }

              /* Update pointers and counts in order to handle partial
               * buffer writes.
               */

              buffer    += nwritten;
              remaining -= nwritten;
              ntotal    += nwritten;
            }
          while (remaining > 0);
        }
    }

  return ntotal;
}