static int
testFileHash ()
{
  int ret;
  FILE *f;

  memset (block, 42, sizeof (block) / 2);
  memset (&block[sizeof (block) / 2], 43, sizeof (block) / 2);
  GNUNET_assert (NULL != (f = FOPEN (FILENAME, "w+")));
  GNUNET_break (sizeof (block) == fwrite (block, 1, sizeof (block), f));
  GNUNET_break (0 == FCLOSE (f));
  ret = 1;
  GNUNET_SCHEDULER_run (&file_hasher, &ret);
  GNUNET_break (0 == UNLINK (FILENAME));
  return ret;
}