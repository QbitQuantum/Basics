int
main (int argc, char **argv)
{
  const char *filename = "test-fgetc.txt";

  /* We don't have an fgetc() function that installs an invalid parameter
     handler so far.  So install that handler here, explicitly.  */
#if HAVE_MSVC_INVALID_PARAMETER_HANDLER \
    && MSVC_INVALID_PARAMETER_HANDLING == DEFAULT_HANDLING
  gl_msvc_inval_ensure_handler ();
#endif

  /* Prepare a file.  */
  {
    const char text[] = "hello world";
    int fd = open (filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    ASSERT (fd >= 0);
    ASSERT (write (fd, text, sizeof (text)) == sizeof (text));
    ASSERT (close (fd) == 0);
  }

  /* Test that fgetc() sets errno if someone else closes the stream
     fd behind the back of stdio.  */
  {
    FILE *fp = fopen (filename, "r");
    ASSERT (fp != NULL);
    ASSERT (close (fileno (fp)) == 0);
    errno = 0;
    ASSERT (fgetc (fp) == EOF);
    ASSERT (errno == EBADF);
    ASSERT (ferror (fp));
    fclose (fp);
  }

  /* Test that fgetc() sets errno if the stream was constructed with
     an invalid file descriptor.  */
  {
    FILE *fp = fdopen (-1, "r");
    if (fp != NULL)
      {
        errno = 0;
        ASSERT (fgetc (fp) == EOF);
        ASSERT (errno == EBADF);
        ASSERT (ferror (fp));
        fclose (fp);
      }
  }
  {
    FILE *fp;
    close (99);
    fp = fdopen (99, "r");
    if (fp != NULL)
      {
        errno = 0;
        ASSERT (fgetc (fp) == EOF);
        ASSERT (errno == EBADF);
        ASSERT (ferror (fp));
        fclose (fp);
      }
  }

  /* Clean up.  */
  unlink (filename);

  return 0;
}