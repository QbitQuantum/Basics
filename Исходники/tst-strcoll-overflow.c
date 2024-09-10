int
do_test (void)
{
  if (setlocale (LC_COLLATE, "en_GB.UTF-8") == NULL)
    {
      puts ("setlocale failed, cannot test for overflow");
      return 0;
    }

  char *p = malloc (SIZE);

  if (p == NULL)
    {
      puts ("could not allocate memory");
      return 1;
    }

  memset (p, 'x', SIZE - 1);
  p[SIZE - 1] = 0;
  printf ("%d\n", strcoll (p, p));
  return 0;
}