static int
do_test (void)
{
  FILE *f = popen ("echo test", "r");
  int result = 0, ret;
  char *line = NULL;
  size_t len = 0;

  if (f == NULL)
    {
      printf ("popen failed %m");
      return 1;
    }

#if __OPTION_POSIX_WIDE_CHAR_DEVICE_IO
  /* POSIX says that pipe streams are byte-oriented.  */
  if (fwide (f, 0) >= 0)
    {
      puts ("popen did not return byte-oriented stream");
      result = 1;
    }
#endif

  if (getline (&line, &len, f) != 5)
    {
      puts ("could not read line from popen");
      result = 1;
    }
  else if (strcmp (line, "test\n") != 0)
    {
      printf ("read \"%s\"\n", line);
      result = 1;
    }

  if (getline (&line, &len, f) != -1)
    {
      puts ("second getline did not return -1");
      result = 1;
    }

  ret = pclose (f);
  if (ret != 0)
    {
      printf ("pclose returned %d\n", ret);
      result = 1;
    }

  return result;
}