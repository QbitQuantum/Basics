int
main (void)
{
  char buf[300];
  int cnt;
  int result = 0;

  for (cnt = 0; cnt < 200; ++cnt)
    {
      ssize_t n;
      float f;

      n = sprintf (buf, "%d", cnt);
      memset (buf + n, '0', cnt);
      sprintf (buf + n + cnt, ".000e-%d", cnt);
      f = strtof (buf, NULL);

      if (f != (float) cnt)
	{
	  printf ("strtof(\"%s\") failed for cnt == %d (%g instead of %g)\n",
		  buf, cnt, f, (float) cnt);
	  result = 1;
	}
      else
	printf ("strtof() fine for cnt == %d\n", cnt);
    }

  for (cnt = 0; cnt < 200; ++cnt)
    {
      ssize_t n;
      double f;

      n = sprintf (buf, "%d", cnt);
      memset (buf + n, '0', cnt);
      sprintf (buf + n + cnt, ".000e-%d", cnt);
      f = strtod (buf, NULL);

      if (f != (double) cnt)
	{
	  printf ("strtod(\"%s\") failed for cnt == %d (%g instead of %g)\n",
		  buf, cnt, f, (double) cnt);
	  result = 1;
	}
      else
	printf ("strtod() fine for cnt == %d\n", cnt);
    }

  for (cnt = 0; cnt < 200; ++cnt)
    {
      ssize_t n;
      long double f;

      n = sprintf (buf, "%d", cnt);
      memset (buf + n, '0', cnt);
      sprintf (buf + n + cnt, ".000e-%d", cnt);
      f = strtold (buf, NULL);

      if (f != (long double) cnt)
	{
	  printf ("strtold(\"%s\") failed for cnt == %d (%Lg instead of %Lg)\n",
		  buf, cnt, f, (long double) cnt);
	  result = 1;
	}
      else
	printf ("strtold() fine for cnt == %d\n", cnt);
    }

  return result;
}