static int
do_test (void)
{
  TEST_VERIFY_EXIT (setlocale (LC_ALL, "de_DE.UTF-8") != NULL);
  /* Fill the stdio buffer and advance the read pointer.  */
  TEST_VERIFY_EXIT (fgetwc (stdin) != WEOF);
  /* This calls _IO_wfile_sync, it should not crash.  */
  TEST_VERIFY_EXIT (setvbuf (stdin, NULL, _IONBF, 0) == 0);
  /* Verify that the external file offset has been synchronized.  */
  TEST_COMPARE (xlseek (0, 0, SEEK_CUR), 1);

  return 0;
}