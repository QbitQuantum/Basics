int
main (int argc, char *argv[])
{
  FILE *fp;

  mtrace ();

  if (argc < 2)
    exit (1);

  fp = fopen (argv[1], "w");
  if (fp == NULL)
    {
      puts ("fopen failed: %m");
      exit (1);
    }

  fputs ("Hello world (mb)\n", fp);

  fp = freopen (argv[1], "a+", fp);
  if (fp == NULL)
    {
      puts ("freopen failed: %m");
      exit (1);
    }

  fputws (L"Hello world (wc)\n", fp);

  fclose (fp);

  return 0;
}