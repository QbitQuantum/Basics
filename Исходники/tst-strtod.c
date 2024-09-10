int
main (int argc, char ** argv)
{
  char buf[100];
  register const struct ltest *lt;
  char *ep;
  int status = 0;
  int save_errno;

  for (lt = tests; lt->str != NULL; ++lt)
    {
      double d;

      errno = 0;
      d = strtod(lt->str, &ep);
      save_errno = errno;
      printf ("strtod (\"%s\") test %u",
	     lt->str, (unsigned int) (lt - tests));
      if (d == lt->expect && *ep == lt->left && save_errno == lt->err)
	puts ("\tOK");
      else
	{
	  puts ("\tBAD");
	  if (d != lt->expect)
	    printf ("  returns %.60g, expected %.60g\n", d, lt->expect);
	  if (lt->left != *ep)
	    {
	      char exp1[5], exp2[5];
	      expand (exp1, *ep);
	      expand (exp2, lt->left);
	      printf ("  leaves '%s', expected '%s'\n", exp1, exp2);
	    }
	  if (save_errno != lt->err)
	    printf ("  errno %d (%s)  instead of %d (%s)\n",
		    save_errno, strerror (save_errno),
		    lt->err, strerror (lt->err));
	  status = 1;
	}
    }

  sprintf (buf, "%f", strtod ("-0.0", NULL));
  if (strcmp (buf, "-0.000000") != 0)
    {
      printf ("  strtod (\"-0.0\", NULL) returns \"%s\"\n", buf);
      status = 1;
    }

  const char input[] = "3752432815e-39";

  float f1 = strtold (input, NULL);
  float f2;
  float f3 = strtof (input, NULL);
  sscanf (input, "%g", &f2);

  if (f1 != f2)
    {
      printf ("f1 = %a != f2 = %a\n", f1, f2);
      status = 1;
    }
  if (f1 != f3)
    {
      printf ("f1 = %a != f3 = %a\n", f1, f3);
      status = 1;
    }
  if (f2 != f3)
    {
      printf ("f2 = %a != f3 = %a\n", f2, f3);
      status = 1;
    }

  const char input2[] = "+1.000000000116415321826934814453125";
  if (strtold (input2, NULL) != +1.000000000116415321826934814453125L)
    {
      printf ("input2: %La != %La\n", strtold (input2, NULL),
	      +1.000000000116415321826934814453125L);
      status = 1;
    }

  status |= long_dbl ();

  status |= locale_test ();

  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}