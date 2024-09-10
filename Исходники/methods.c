void
newton (long double p0, long double b, long double error, long double p,
	long double (*f) (long double, long double), char *name)
{
  long double p1, fb, fc, c, test;
  int n = 0;

  printf ("  Starting newton %s with min accuracy of %Lf\n", name, error);
  printf ("      p0            p1               test \n");

  do
    {
      p1 = p0 - f (p0, 0) / f (p0, 1);

      if (isnan (p1))
	goto fail;

      test = fabsl (p0 - p1);

      printf ("  %12.6Lf   %12.6Lf   %12.6Lf   \n", p0, p1, test);
      p0 = p1;

      // fail gracefully
      n++;
      if (n > 20)
	{
	  printf ("  *** This method is failing, use another technique \n");
	  break;
	}

    }
  while (test > error);

fail:
  printf ("  Best Guess:     %0.17Lf \n", p1);
  printf ("  Error Estimate: %0.17Lf \n", test);

  printf ("  Stopping newton %s\n\n", name);

}