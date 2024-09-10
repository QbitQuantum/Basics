/* Test which should fail.  */
static int
fail_test (int c)
{
  wint_t wc = btowc (c);

  if (wc != WEOF)
    {
      printf ("%s: btowc('%c') succeded, returned L'\\x%x' instead of WEOF\n",
	      current_locale, c, wc);
      return 1;
    }

  return 0;
}