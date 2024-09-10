static int
do_test (void)
{
  mtrace ();

  char *temp_file;
  TEST_VERIFY_EXIT (create_temp_file ("tst-bz22145.", &temp_file));

  char buf[BUFSIZ];

  {
    /* Check if backup buffer is correctly freed and changing back
       to normal buffer does not trigger an invalid free in case of
       static buffer set by setvbuf.  */

    FILE *f = fopen (temp_file, "w+b");
    TEST_VERIFY_EXIT (f != NULL);

    TEST_VERIFY_EXIT (setvbuf (f, buf, _IOFBF, BUFSIZ) == 0);
    TEST_VERIFY_EXIT (ungetc ('x', f) == 'x');
    TEST_VERIFY_EXIT (fseek (f, 0L, SEEK_SET) == 0);
    TEST_VERIFY_EXIT (fputc ('y', f) ==  'y');

    TEST_VERIFY_EXIT (fclose (f) == 0);
  }

  {
    /* Check if backup buffer is correctly freed and changing back
       to normal buffer does not trigger an invalid free in case of
       static buffer set by setvbuf.  */

    FILE *f = fopen (temp_file, "w+b");
    TEST_VERIFY_EXIT (f != NULL);

    TEST_VERIFY_EXIT (setvbuf (f, buf, _IOFBF, BUFSIZ) == 0);
    TEST_VERIFY_EXIT (ungetc ('x', f) == 'x');
    TEST_VERIFY_EXIT (fputc ('y', f) ==  'y');

    TEST_VERIFY_EXIT (fclose (f) == 0);
  }

  {
    FILE *f = fopen (temp_file, "w+b");
    TEST_VERIFY_EXIT (f != NULL);

    TEST_VERIFY_EXIT (setvbuf (f, buf, _IOFBF, BUFSIZ) == 0);
    TEST_VERIFY_EXIT (ungetwc (L'x', f) == L'x');
    TEST_VERIFY_EXIT (fseek (f, 0L, SEEK_SET) == 0);
    TEST_VERIFY_EXIT (fputwc (L'y', f) ==  L'y');

    TEST_VERIFY_EXIT (fclose (f) == 0);
  }

  {
    FILE *f = fopen (temp_file, "w+b");
    TEST_VERIFY_EXIT (f != NULL);

    TEST_VERIFY_EXIT (setvbuf (f, buf, _IOFBF, BUFSIZ) == 0);
    TEST_VERIFY_EXIT (ungetwc (L'x', f) == L'x');
    TEST_VERIFY_EXIT (fputwc (L'y', f) ==  L'y');

    TEST_VERIFY_EXIT (fclose (f) == 0);
  }

  free (temp_file);

  return 0;
}