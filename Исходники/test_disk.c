static int
testReadWrite ()
{
  char tmp[100 + 1];
  int ret;

  if (strlen (TESTSTRING) !=
      GNUNET_DISK_fn_write (".testfile", TESTSTRING, strlen (TESTSTRING),
                            GNUNET_DISK_PERM_USER_READ |
                            GNUNET_DISK_PERM_USER_WRITE))
    return 1;
  if (GNUNET_OK != GNUNET_DISK_file_test (".testfile"))
    return 1;
  ret = GNUNET_DISK_fn_read (".testfile", tmp, sizeof (tmp) - 1);
  if (ret < 0)
  {
    FPRINTF (stderr, "Error reading file `%s' in testReadWrite\n", ".testfile");
    return 1;
  }
  tmp[ret] = '\0';
  if (0 != memcmp (tmp, TESTSTRING, strlen (TESTSTRING) + 1))
  {
    FPRINTF (stderr, "Error in testReadWrite: *%s* != *%s* for file %s\n", tmp,
             TESTSTRING, ".testfile");
    return 1;
  }
  GNUNET_DISK_file_copy (".testfile", ".testfile2");
  memset (tmp, 0, sizeof (tmp));
  ret = GNUNET_DISK_fn_read (".testfile2", tmp, sizeof (tmp) - 1);
  if (ret < 0)
  {
    FPRINTF (stderr, "Error reading file `%s' in testReadWrite\n",
             ".testfile2");
    return 1;
  }
  tmp[ret] = '\0';
  if (0 != memcmp (tmp, TESTSTRING, strlen (TESTSTRING) + 1))
  {
    FPRINTF (stderr, "Error in testReadWrite: *%s* != *%s* for file %s\n", tmp,
             TESTSTRING, ".testfile2");
    return 1;
  }

  GNUNET_break (0 == UNLINK (".testfile"));
  GNUNET_break (0 == UNLINK (".testfile2"));
  if (GNUNET_NO != GNUNET_DISK_file_test (".testfile"))
    return 1;

  return 0;
}