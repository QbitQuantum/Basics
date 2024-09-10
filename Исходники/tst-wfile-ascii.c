static int
do_test (void)
{
  /* The test-in-container framework sets these environment variables.
     The presence of GCONV_PATH invalidates this test.  */
  unsetenv ("GCONV_PATH");
  unsetenv ("LOCPATH");

  /* Create the gconv module cache.  iconvconfig is in /sbin, which is
     not on PATH.  */
  {
    char *iconvconfig = xasprintf ("%s/iconvconfig", support_sbindir_prefix);
    TEST_COMPARE (system (iconvconfig), 0);
  }

  /* Use built-in ASCII gconv module, without triggering cache
     initialization.  */
  FILE *fp1 = xfopen ("/dev/zero", "r");
  TEST_COMPARE (fwide (fp1, 1), 1);

  /* Use non-ASCII gconv module and trigger gconv cache
     initialization.  */
  FILE *fp2 = xfopen ("/dev/zero", "r,ccs=UTF-8");
  TEST_COMPARE (fwide (fp2, 0), 1);

  xfclose (fp1);
  xfclose (fp2);

  return 0;
}