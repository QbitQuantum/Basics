static int
do_test (void)
{
  double d[6];
  long l[6];
  int i, j;
  int tst_locale;
  int result = 0;

  tst_locale = 1;
  if (tst_locale)
    if (setlocale (LC_ALL, "en_US.ISO-8859-1") == NULL)
      {
	puts ("Failed to set en_US locale, skipping locale related tests");
	tst_locale = 0;
      }

  for (i = 0; i < 4; ++i)
    {
      if (SSCANF (str_double[i], L("%11lf%11lf%11lf%11lf%11lf%11lf"),
		  &d[0], &d[1], &d[2], &d[3], &d[4], &d[5]) != 6)
	{
	  printf ("Double sscanf test %d wrong number of "
		  "assigned inputs\n", i);
	  result = 1;
	}
      else
	for (j = 0; j < 6; ++j)
	  if (d[j] != val_double[6 * i + j])
	    {
	      printf ("Double sscanf test %d failed (%g instead of %g)\n",
		      i, d[j], val_double[6 * i + j]);
	      result = 1;
	      break;
	    }
    }

  for (i = 0; i < 4; ++i)
    {
      if (SSCANF (str_long[i], fmt_long[i],
		  &l[0], &l[1], &l[2], &l[3], &l[4], &l[5]) != 6)
	{
	  printf ("Integer sscanf test %d wrong number of "
		  "assigned inputs\n", i);
	  result = 1;
	}
      else
	for (j = 0; j < 6; ++j)
	  if (l[j] != val_long[j])
	    {
	      printf ("Integer sscanf test %d failed (%ld instead %ld)\n",
		      i, l[j], val_long[j]);
	      result = 1;
	      break;
	    }

      if (! tst_locale)
	break;
    }

  for (i = 0; i < sizeof (int_tests) / sizeof (int_tests[0]); ++i)
    {
      long dummy;
      int ret;

      if ((ret = SSCANF (int_tests[i].str, int_tests[i].fmt,
			 &dummy)) != int_tests[i].retval)
	{
	  printf ("int_tests[%d] returned %d != %d\n",
		  i, ret, int_tests[i].retval);
	  result = 1;
	}
    }

  for (i = 0; i < sizeof (double_tests) / sizeof (double_tests[0]); ++i)
    {
      double dummy;
      int ret;

      if ((ret = SSCANF (double_tests[i].str, double_tests[i].fmt,
			 &dummy)) != double_tests[i].retval)
	{
	  printf ("double_tests[%d] returned %d != %d\n",
		  i, ret, double_tests[i].retval);
	  result = 1;
	}
    }

  for (i = 0; i < sizeof (double_tests2) / sizeof (double_tests2[0]); ++i)
    {
      double dummy;
      int ret;
      char c = 0;

      if ((ret = SSCANF (double_tests2[i].str, double_tests2[i].fmt,
			 &dummy, &c)) != double_tests2[i].retval)
	{
	  printf ("double_tests2[%d] returned %d != %d\n",
		  i, ret, double_tests2[i].retval);
	  result = 1;
	}
      else if (ret == 2 && c != double_tests2[i].residual)
	{
	  printf ("double_tests2[%d] stopped at '%c' != '%c'\n",
		  i, c, double_tests2[i].residual);
	  result = 1;
	}
    }

  /* BZ #16618
     The test will segfault during SSCANF if the buffer overflow
     is not fixed.  The size of `s` is such that it forces the use
     of malloc internally and this triggers the incorrect computation.
     Thus the value for SIZE is arbitrariy high enough that malloc
     is used.  */
  {
#define SIZE 131072
    CHAR *s = malloc ((SIZE + 1) * sizeof (*s));
    if (s == NULL)
      abort ();
    for (size_t i = 0; i < SIZE; i++)
      s[i] = L('0');
    s[SIZE] = L('\0');
    int i = 42;
    /* Scan multi-digit zero into `i`.  */
    if (SSCANF (s, L("%d"), &i) != 1)
      {
	printf ("FAIL: bug16618: SSCANF did not read one input item.\n");
	result = 1;
      }
    if (i != 0)
      {
	printf ("FAIL: bug16618: Value of `i` was not zero as expected.\n");
	result = 1;
      }
    free (s);
    if (result != 1)
      printf ("PASS: bug16618: Did not crash.\n");
#undef SIZE
  }


  return result;
}