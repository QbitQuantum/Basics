ssize_t lib_fread(FAR void *ptr, size_t count, FAR FILE *stream)
{
  unsigned char *dest  = (unsigned char*)ptr;
  ssize_t        bytes_read;
#if CONFIG_STDIO_BUFFER_SIZE > 0
  int            ret;
#endif

  /* Make sure that reading from this stream is allowed */

  if (!stream || (stream->fs_oflags & O_RDOK) == 0)
    {
      set_errno(EBADF);
      bytes_read = -1;
    }
  else
    {
      /* The stream must be stable until we complete the read */

      lib_take_semaphore(stream);

#if CONFIG_NUNGET_CHARS > 0
      /* First, re-read any previously ungotten characters */

      while ((stream->fs_nungotten > 0) && (count > 0))
        {
          /* Decrement the count of ungotten bytes to get an index */

          stream->fs_nungotten--;

          /* Return the last ungotten byte */

          *dest++ = stream->fs_ungotten[stream->fs_nungotten];

          /* That's one less byte that we have to read */

          count--;
        }
#endif

#if CONFIG_STDIO_BUFFER_SIZE > 0
      /* If the buffer is currently being used for write access, then
       * flush all of the buffered write data.  We do not support concurrent
       * buffered read/write access.
       */

      ret = lib_wrflush(stream);
      if (ret < 0)
        {
          lib_give_semaphore(stream);
          return ret;
        }

      /* Now get any other needed chars from the buffer or the file. */

      while (count > 0)
        {
          /* Is there readable data in the buffer? */

          while ((count > 0) && (stream->fs_bufpos < stream->fs_bufread))
            {
              /* Yes, copy a byte into the user buffer */

              *dest++ = *stream->fs_bufpos++;
              count--;
            }

          /* The buffer is empty OR we have already supplied the number of
           * bytes requested in the read.  Check if we need to read
           * more from the file.
           */

          if (count > 0)
            {
              size_t buffer_available;

              /* We need to read more data into the buffer from the file */

              /* Mark the buffer empty */

              stream->fs_bufpos = stream->fs_bufread = stream->fs_bufstart;

              /* How much space is available in the buffer? */

              buffer_available = stream->fs_bufend - stream->fs_bufread;

              /* Will the number of bytes that we need to read fit into
               * the buffer space that is available? If the read size is
               * larger than the buffer, then read some of the data
               * directly into the user's buffer.
               */

              if (count > buffer_available)
                {
                  bytes_read = read(stream->fs_fd, dest, count);
                  if (bytes_read < 0)
                    {
                      /* An error occurred on the read.  The error code is
                       * in the 'errno' variable.
                       */

                      goto errout_with_errno;
                    }
                  else if (bytes_read == 0)
                    {
                      /* We are at the end of the file.  But we may already
                       * have buffered data.  In that case, we will report
                       * the EOF indication later.
                       */

                      goto shortread;
                    }
                  else
                    {
                      /* Some bytes were read. Adjust the dest pointer */

                      dest  += bytes_read;

                      /* Were all of the requested bytes read? */

                      if ((size_t)bytes_read < count)
                        {
                          /* No.  We must be at the end of file. */

                          goto shortread;
                        }
                      else
                        {
                          /* Yes.  We are done. */

                          count = 0;
                        }
                    }
                }
              else
                {
                  /* The number of bytes required to satisfy the read
                   * is less than or equal to the size of the buffer
                   * space that we have left. Read as much as we can
                   * into the buffer.
                   */

                  bytes_read = read(stream->fs_fd, stream->fs_bufread, buffer_available);
                  if (bytes_read < 0)
                    {
                      /* An error occurred on the read.  The error code is
                       * in the 'errno' variable.
                       */

                      goto errout_with_errno;
                    }
                  else if (bytes_read == 0)
                    {
                      /* We are at the end of the file.  But we may already
                       * have buffered data.  In that case, we will report
                       * the EOF indication later.
                       */

                      goto shortread;
                    }
                  else
                    {
                      /* Some bytes were read */

                      stream->fs_bufread += bytes_read;
                    }
                }
            }
        }
#else
      /* Now get any other needed chars from the file. */

      while (count > 0)
        {
          bytes_read = read(stream->fs_fd, dest, count);
          if (bytes_read < 0)
            {
              /* An error occurred on the read.  The error code is
               * in the 'errno' variable.
               */

              goto errout_with_errno;
            }
          else if (bytes_read == 0)
            {
              /* We are at the end of the file.  But we may already
               * have buffered data.  In that case, we will report
               * the EOF indication later.
               */

              break;
            }
          else
            {
              dest  += bytes_read;
              count -= bytes_read;
            }
        }
#endif
      /* Here after a successful (but perhaps short) read */

#if CONFIG_STDIO_BUFFER_SIZE > 0
    shortread:
#endif
      bytes_read = dest - (unsigned char*)ptr;

      /* Set or clear the EOF indicator.  If we get here because of a
       * short read and the total number of* bytes read is zero, then
       * we must be at the end-of-file.
       */

      if (bytes_read > 0)
        {
          stream->fs_flags &= ~__FS_FLAG_EOF;
        }
      else
        {
          stream->fs_flags |= __FS_FLAG_EOF;
        }

      lib_give_semaphore(stream);
    }

  return bytes_read;

/* Error exits */

errout_with_errno:
  stream->fs_flags |= __FS_FLAG_ERROR;
  lib_give_semaphore(stream);
  return -get_errno();
}