int
main (int argc, char *argv[])
{
  struct GNUNET_DISK_FileHandle *fh;
  struct GNUNET_HELLO_Message *orig;
  struct GNUNET_HELLO_Message *result;
  struct GNUNET_CRYPTO_RsaPublicKeyBinaryEncoded pk;
  uint64_t fsize;

  GNUNET_log_setup ("gnunet-hello", "INFO", NULL);
  if (argc != 2)
  {
    FPRINTF (stderr,
	     "%s",
	     _("Call with name of HELLO file to modify.\n"));
    return 1;
  }
  if (GNUNET_OK != GNUNET_DISK_file_size (argv[1], &fsize, GNUNET_YES, GNUNET_YES))
  {
    FPRINTF (stderr,
	     _("Error accessing file `%s': %s\n"),
	     argv[1],
	     STRERROR (errno));
    return 1;
  }
  if (fsize > 65536)
  {
    FPRINTF (stderr,
	     _("File `%s' is too big to be a HELLO\n"),
	     argv[1]);
    return 1;
  }
  if (fsize < sizeof (struct GNUNET_MessageHeader))
  {
    FPRINTF (stderr,
	     _("File `%s' is too small to be a HELLO\n"),
	     argv[1]);
    return 1;
  }
  fh = GNUNET_DISK_file_open (argv[1], 
			      GNUNET_DISK_OPEN_READ,
			      GNUNET_DISK_PERM_USER_READ);
  if (NULL == fh)
  {
    FPRINTF (stderr,
	     _("Error opening file `%s': %s\n"),
	     argv[1],
	     STRERROR (errno));
    return 1;
  }
  {
    char buf[fsize] GNUNET_ALIGN;
    
    GNUNET_assert (fsize == 
		   GNUNET_DISK_file_read (fh, buf, fsize));
    GNUNET_assert (GNUNET_OK == GNUNET_DISK_file_close (fh));
    orig = (struct GNUNET_HELLO_Message *) buf;
    if ( (fsize != GNUNET_HELLO_size (orig)) ||
	 (GNUNET_OK != GNUNET_HELLO_get_key (orig, &pk)) )
    {
      FPRINTF (stderr,
	       _("Did not find well-formed HELLO in file `%s'\n"),
	       argv[1]);
      return 1;
    }
    result = GNUNET_HELLO_create (&pk, &add_from_hello, &orig);
    GNUNET_assert (NULL != result);
     fh = GNUNET_DISK_file_open (argv[1], 
				 GNUNET_DISK_OPEN_WRITE,
				 GNUNET_DISK_PERM_USER_READ | GNUNET_DISK_PERM_USER_WRITE);
     if (NULL == fh)
     {
       FPRINTF (stderr,
		_("Error opening file `%s': %s\n"),
		argv[1],
		STRERROR (errno));
       GNUNET_free (result);
       return 1;
     }
     fsize = GNUNET_HELLO_size (result);
     if (fsize != GNUNET_DISK_file_write (fh,
					  result,
					  fsize))
     {
       FPRINTF (stderr,
		_("Error writing HELLO to file `%s': %s\n"),
		argv[1],
		STRERROR (errno));
       (void) GNUNET_DISK_file_close (fh);
       return 1;
     }
    GNUNET_assert (GNUNET_OK == GNUNET_DISK_file_close (fh));
  }
  return 0;
}