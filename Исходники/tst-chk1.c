static int
do_test (void)
{
  struct sigaction sa;
  sa.sa_handler = handler;
  sa.sa_flags = 0;
  sigemptyset (&sa.sa_mask);

  sigaction (SIGABRT, &sa, NULL);

  /* Avoid all the buffer overflow messages on stderr.  */
  int fd = open (_PATH_DEVNULL, O_WRONLY);
  if (fd == -1)
    close (STDERR_FILENO);
  else
    {
      dup2 (fd, STDERR_FILENO);
      close (fd);
    }
  setenv ("LIBC_FATAL_STDERR_", "1", 1);

  struct A { char buf1[9]; char buf2[1]; } a;
  struct wA { wchar_t buf1[9]; wchar_t buf2[1]; } wa;

  printf ("Test checking routines at fortify level %d\n",
#ifdef __USE_FORTIFY_LEVEL
	  (int) __USE_FORTIFY_LEVEL
#else
	  0
#endif
	  );

  /* These ops can be done without runtime checking of object size.  */
  memcpy (buf, "abcdefghij", 10);
  memmove (buf + 1, buf, 9);
  if (memcmp (buf, "aabcdefghi", 10))
    FAIL ();

  if (mempcpy (buf + 5, "abcde", 5) != buf + 10
      || memcmp (buf, "aabcdabcde", 10))
    FAIL ();

  memset (buf + 8, 'j', 2);
  if (memcmp (buf, "aabcdabcjj", 10))
    FAIL ();

  strcpy (buf + 4, "EDCBA");
  if (memcmp (buf, "aabcEDCBA", 10))
    FAIL ();

  if (stpcpy (buf + 8, "F") != buf + 9 || memcmp (buf, "aabcEDCBF", 10))
    FAIL ();

  strncpy (buf + 6, "X", 4);
  if (memcmp (buf, "aabcEDX\0\0", 10))
    FAIL ();

  if (sprintf (buf + 7, "%s", "67") != 2 || memcmp (buf, "aabcEDX67", 10))
    FAIL ();

  if (snprintf (buf + 7, 3, "%s", "987654") != 6
      || memcmp (buf, "aabcEDX98", 10))
    FAIL ();

  /* These ops need runtime checking, but shouldn't __chk_fail.  */
  memcpy (buf, "abcdefghij", l0 + 10);
  memmove (buf + 1, buf, l0 + 9);
  if (memcmp (buf, "aabcdefghi", 10))
    FAIL ();

  if (mempcpy (buf + 5, "abcde", l0 + 5) != buf + 10
      || memcmp (buf, "aabcdabcde", 10))
    FAIL ();

  memset (buf + 8, 'j', l0 + 2);
  if (memcmp (buf, "aabcdabcjj", 10))
    FAIL ();

  strcpy (buf + 4, str1 + 5);
  if (memcmp (buf, "aabcEDCBA", 10))
    FAIL ();

  if (stpcpy (buf + 8, str2) != buf + 9 || memcmp (buf, "aabcEDCBF", 10))
    FAIL ();

  strncpy (buf + 6, "X", l0 + 4);
  if (memcmp (buf, "aabcEDX\0\0", 10))
    FAIL ();

  if (stpncpy (buf + 5, "cd", l0 + 5) != buf + 7
      || memcmp (buf, "aabcEcd\0\0", 10))
    FAIL ();

  if (sprintf (buf + 7, "%d", num1) != 2 || memcmp (buf, "aabcEcd67", 10))
    FAIL ();

  if (snprintf (buf + 7, 3, "%d", num2) != 6 || memcmp (buf, "aabcEcd98", 10))
    FAIL ();

  buf[l0 + 8] = '\0';
  strcat (buf, "A");
  if (memcmp (buf, "aabcEcd9A", 10))
    FAIL ();

  buf[l0 + 7] = '\0';
  strncat (buf, "ZYXWV", l0 + 2);
  if (memcmp (buf, "aabcEcdZY", 10))
    FAIL ();

  memcpy (a.buf1, "abcdefghij", l0 + 10);
  memmove (a.buf1 + 1, a.buf1, l0 + 9);
  if (memcmp (a.buf1, "aabcdefghi", 10))
    FAIL ();

  if (mempcpy (a.buf1 + 5, "abcde", l0 + 5) != a.buf1 + 10
      || memcmp (a.buf1, "aabcdabcde", 10))
    FAIL ();

  memset (a.buf1 + 8, 'j', l0 + 2);
  if (memcmp (a.buf1, "aabcdabcjj", 10))
    FAIL ();

#if __USE_FORTIFY_LEVEL < 2
  /* The following tests are supposed to crash with -D_FORTIFY_SOURCE=2
     and sufficient GCC support, as the string operations overflow
     from a.buf1 into a.buf2.  */
  strcpy (a.buf1 + 4, str1 + 5);
  if (memcmp (a.buf1, "aabcEDCBA", 10))
    FAIL ();

  if (stpcpy (a.buf1 + 8, str2) != a.buf1 + 9
      || memcmp (a.buf1, "aabcEDCBF", 10))
    FAIL ();

  strncpy (a.buf1 + 6, "X", l0 + 4);
  if (memcmp (a.buf1, "aabcEDX\0\0", 10))
    FAIL ();

  if (sprintf (a.buf1 + 7, "%d", num1) != 2
      || memcmp (a.buf1, "aabcEDX67", 10))
    FAIL ();

  if (snprintf (a.buf1 + 7, 3, "%d", num2) != 6
      || memcmp (a.buf1, "aabcEDX98", 10))
    FAIL ();

  a.buf1[l0 + 8] = '\0';
  strcat (a.buf1, "A");
  if (memcmp (a.buf1, "aabcEDX9A", 10))
    FAIL ();

  a.buf1[l0 + 7] = '\0';
  strncat (a.buf1, "ZYXWV", l0 + 2);
  if (memcmp (a.buf1, "aabcEDXZY", 10))
    FAIL ();

#endif

#if __USE_FORTIFY_LEVEL >= 1
  /* Now check if all buffer overflows are caught at runtime.  */

  CHK_FAIL_START
  memcpy (buf + 1, "abcdefghij", l0 + 10);
  CHK_FAIL_END

  CHK_FAIL_START
  memmove (buf + 2, buf + 1, l0 + 9);
  CHK_FAIL_END

  CHK_FAIL_START
  p = mempcpy (buf + 6, "abcde", l0 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  memset (buf + 9, 'j', l0 + 2);
  CHK_FAIL_END

  CHK_FAIL_START
  strcpy (buf + 5, str1 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  p = stpcpy (buf + 9, str2);
  CHK_FAIL_END

  CHK_FAIL_START
  strncpy (buf + 7, "X", l0 + 4);
  CHK_FAIL_END

  CHK_FAIL_START
  stpncpy (buf + 6, "cd", l0 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  sprintf (buf + 8, "%d", num1);
  CHK_FAIL_END

  CHK_FAIL_START
  snprintf (buf + 8, l0 + 3, "%d", num2);
  CHK_FAIL_END

  memcpy (buf, str1 + 2, l0 + 9);
  CHK_FAIL_START
  strcat (buf, "AB");
  CHK_FAIL_END

  memcpy (buf, str1 + 3, l0 + 8);
  CHK_FAIL_START
  strncat (buf, "ZYXWV", l0 + 3);
  CHK_FAIL_END

  CHK_FAIL_START
  memcpy (a.buf1 + 1, "abcdefghij", l0 + 10);
  CHK_FAIL_END

  CHK_FAIL_START
  memmove (a.buf1 + 2, a.buf1 + 1, l0 + 9);
  CHK_FAIL_END

  CHK_FAIL_START
  p = mempcpy (a.buf1 + 6, "abcde", l0 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  memset (a.buf1 + 9, 'j', l0 + 2);
  CHK_FAIL_END

#if __USE_FORTIFY_LEVEL >= 2
# define O 0
#else
# define O 1
#endif

  CHK_FAIL_START
  strcpy (a.buf1 + (O + 4), str1 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  p = stpcpy (a.buf1 + (O + 8), str2);
  CHK_FAIL_END

  CHK_FAIL_START
  strncpy (a.buf1 + (O + 6), "X", l0 + 4);
  CHK_FAIL_END

  CHK_FAIL_START
  sprintf (a.buf1 + (O + 7), "%d", num1);
  CHK_FAIL_END

  CHK_FAIL_START
  snprintf (a.buf1 + (O + 7), l0 + 3, "%d", num2);
  CHK_FAIL_END

  memcpy (a.buf1, str1 + (3 - O), l0 + 8 + O);
  CHK_FAIL_START
  strcat (a.buf1, "AB");
  CHK_FAIL_END

  memcpy (a.buf1, str1 + (4 - O), l0 + 7 + O);
  CHK_FAIL_START
  strncat (a.buf1, "ZYXWV", l0 + 3);
  CHK_FAIL_END
#endif


  /* These ops can be done without runtime checking of object size.  */
  wmemcpy (wbuf, L"abcdefghij", 10);
  wmemmove (wbuf + 1, wbuf, 9);
  if (wmemcmp (wbuf, L"aabcdefghi", 10))
    FAIL ();

  if (wmempcpy (wbuf + 5, L"abcde", 5) != wbuf + 10
      || wmemcmp (wbuf, L"aabcdabcde", 10))
    FAIL ();

  wmemset (wbuf + 8, L'j', 2);
  if (wmemcmp (wbuf, L"aabcdabcjj", 10))
    FAIL ();

  wcscpy (wbuf + 4, L"EDCBA");
  if (wmemcmp (wbuf, L"aabcEDCBA", 10))
    FAIL ();

  if (wcpcpy (wbuf + 8, L"F") != wbuf + 9 || wmemcmp (wbuf, L"aabcEDCBF", 10))
    FAIL ();

  wcsncpy (wbuf + 6, L"X", 4);
  if (wmemcmp (wbuf, L"aabcEDX\0\0", 10))
    FAIL ();

  if (swprintf (wbuf + 7, 3, L"%ls", L"987654") >= 0
      || wmemcmp (wbuf, L"aabcEDX98", 10))
    FAIL ();

  if (swprintf (wbuf + 7, 3, L"64") != 2
      || wmemcmp (wbuf, L"aabcEDX64", 10))
    FAIL ();

  /* These ops need runtime checking, but shouldn't __chk_fail.  */
  wmemcpy (wbuf, L"abcdefghij", l0 + 10);
  wmemmove (wbuf + 1, wbuf, l0 + 9);
  if (wmemcmp (wbuf, L"aabcdefghi", 10))
    FAIL ();

  if (wmempcpy (wbuf + 5, L"abcde", l0 + 5) != wbuf + 10
      || wmemcmp (wbuf, L"aabcdabcde", 10))
    FAIL ();

  wmemset (wbuf + 8, L'j', l0 + 2);
  if (wmemcmp (wbuf, L"aabcdabcjj", 10))
    FAIL ();

  wcscpy (wbuf + 4, wstr1 + 5);
  if (wmemcmp (wbuf, L"aabcEDCBA", 10))
    FAIL ();

  if (wcpcpy (wbuf + 8, wstr2) != wbuf + 9 || wmemcmp (wbuf, L"aabcEDCBF", 10))
    FAIL ();

  wcsncpy (wbuf + 6, L"X", l0 + 4);
  if (wmemcmp (wbuf, L"aabcEDX\0\0", 10))
    FAIL ();

  if (wcpncpy (wbuf + 5, L"cd", l0 + 5) != wbuf + 7
      || wmemcmp (wbuf, L"aabcEcd\0\0", 10))
    FAIL ();

  if (swprintf (wbuf + 7, 3, L"%d", num2) >= 0
      || wmemcmp (wbuf, L"aabcEcd98", 10))
    FAIL ();

  wbuf[l0 + 8] = L'\0';
  wcscat (wbuf, L"A");
  if (wmemcmp (wbuf, L"aabcEcd9A", 10))
    FAIL ();

  wbuf[l0 + 7] = L'\0';
  wcsncat (wbuf, L"ZYXWV", l0 + 2);
  if (wmemcmp (wbuf, L"aabcEcdZY", 10))
    FAIL ();

  wmemcpy (wa.buf1, L"abcdefghij", l0 + 10);
  wmemmove (wa.buf1 + 1, wa.buf1, l0 + 9);
  if (wmemcmp (wa.buf1, L"aabcdefghi", 10))
    FAIL ();

  if (wmempcpy (wa.buf1 + 5, L"abcde", l0 + 5) != wa.buf1 + 10
      || wmemcmp (wa.buf1, L"aabcdabcde", 10))
    FAIL ();

  wmemset (wa.buf1 + 8, L'j', l0 + 2);
  if (wmemcmp (wa.buf1, L"aabcdabcjj", 10))
    FAIL ();

#if __USE_FORTIFY_LEVEL < 2
  /* The following tests are supposed to crash with -D_FORTIFY_SOURCE=2
     and sufficient GCC support, as the string operations overflow
     from a.buf1 into a.buf2.  */
  wcscpy (wa.buf1 + 4, wstr1 + 5);
  if (wmemcmp (wa.buf1, L"aabcEDCBA", 10))
    FAIL ();

  if (wcpcpy (wa.buf1 + 8, wstr2) != wa.buf1 + 9
      || wmemcmp (wa.buf1, L"aabcEDCBF", 10))
    FAIL ();

  wcsncpy (wa.buf1 + 6, L"X", l0 + 4);
  if (wmemcmp (wa.buf1, L"aabcEDX\0\0", 10))
    FAIL ();

  if (swprintf (wa.buf1 + 7, 3, L"%d", num2) >= 0
      || wmemcmp (wa.buf1, L"aabcEDX98", 10))
    FAIL ();

  wa.buf1[l0 + 8] = L'\0';
  wcscat (wa.buf1, L"A");
  if (wmemcmp (wa.buf1, L"aabcEDX9A", 10))
    FAIL ();

  wa.buf1[l0 + 7] = L'\0';
  wcsncat (wa.buf1, L"ZYXWV", l0 + 2);
  if (wmemcmp (wa.buf1, L"aabcEDXZY", 10))
    FAIL ();

#endif

#if __USE_FORTIFY_LEVEL >= 1
  /* Now check if all buffer overflows are caught at runtime.  */

  CHK_FAIL_START
  wmemcpy (wbuf + 1, L"abcdefghij", l0 + 10);
  CHK_FAIL_END

  CHK_FAIL_START
  wmemmove (wbuf + 2, wbuf + 1, l0 + 9);
  CHK_FAIL_END

  CHK_FAIL_START
    wp = wmempcpy (wbuf + 6, L"abcde", l0 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  wmemset (wbuf + 9, L'j', l0 + 2);
  CHK_FAIL_END

  CHK_FAIL_START
  wcscpy (wbuf + 5, wstr1 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  wp = wcpcpy (wbuf + 9, wstr2);
  CHK_FAIL_END

  CHK_FAIL_START
  wcsncpy (wbuf + 7, L"X", l0 + 4);
  CHK_FAIL_END

  CHK_FAIL_START
  wcpncpy (wbuf + 6, L"cd", l0 + 5);
  CHK_FAIL_END

  wmemcpy (wbuf, wstr1 + 2, l0 + 9);
  CHK_FAIL_START
  wcscat (wbuf, L"AB");
  CHK_FAIL_END

  wmemcpy (wbuf, wstr1 + 3, l0 + 8);
  CHK_FAIL_START
  wcsncat (wbuf, L"ZYXWV", l0 + 3);
  CHK_FAIL_END

  CHK_FAIL_START
  wmemcpy (wa.buf1 + 1, L"abcdefghij", l0 + 10);
  CHK_FAIL_END

  CHK_FAIL_START
  wmemmove (wa.buf1 + 2, wa.buf1 + 1, l0 + 9);
  CHK_FAIL_END

  CHK_FAIL_START
  wp = wmempcpy (wa.buf1 + 6, L"abcde", l0 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  wmemset (wa.buf1 + 9, L'j', l0 + 2);
  CHK_FAIL_END

#if __USE_FORTIFY_LEVEL >= 2
# define O 0
#else
# define O 1
#endif

  CHK_FAIL_START
  wcscpy (wa.buf1 + (O + 4), wstr1 + 5);
  CHK_FAIL_END

  CHK_FAIL_START
  wp = wcpcpy (wa.buf1 + (O + 8), wstr2);
  CHK_FAIL_END

  CHK_FAIL_START
  wcsncpy (wa.buf1 + (O + 6), L"X", l0 + 4);
  CHK_FAIL_END

  wmemcpy (wa.buf1, wstr1 + (3 - O), l0 + 8 + O);
  CHK_FAIL_START
  wcscat (wa.buf1, L"AB");
  CHK_FAIL_END

  wmemcpy (wa.buf1, wstr1 + (4 - O), l0 + 7 + O);
  CHK_FAIL_START
  wcsncat (wa.buf1, L"ZYXWV", l0 + 3);
  CHK_FAIL_END
#endif


  /* Now checks for %n protection.  */

  /* Constant literals passed directly are always ok
     (even with warnings about possible bugs from GCC).  */
  int n1, n2;
  if (sprintf (buf, "%s%n%s%n", str2, &n1, str2, &n2) != 2
      || n1 != 1 || n2 != 2)
    FAIL ();

  /* In this case the format string is not known at compile time,
     but resides in read-only memory, so is ok.  */
  if (snprintf (buf, 4, str3, str2, &n1, str2, &n2) != 2
      || n1 != 1 || n2 != 2)
    FAIL ();

  strcpy (buf2 + 2, "%n%s%n");
  /* When the format string is writable and contains %n,
     with -D_FORTIFY_SOURCE=2 it causes __chk_fail.  */
  CHK_FAIL2_START
  if (sprintf (buf, buf2, str2, &n1, str2, &n1) != 2)
    FAIL ();
  CHK_FAIL2_END

  CHK_FAIL2_START
  if (snprintf (buf, 3, buf2, str2, &n1, str2, &n1) != 2)
    FAIL ();
  CHK_FAIL2_END

  /* But if there is no %n, even writable format string
     should work.  */
  buf2[6] = '\0';
  if (sprintf (buf, buf2 + 4, str2) != 1)
    FAIL ();

  /* Constant literals passed directly are always ok
     (even with warnings about possible bugs from GCC).  */
  if (printf ("%s%n%s%n", str4, &n1, str5, &n2) != 14
      || n1 != 7 || n2 != 14)
    FAIL ();

  /* In this case the format string is not known at compile time,
     but resides in read-only memory, so is ok.  */
  if (printf (str3, str4, &n1, str5, &n2) != 14
      || n1 != 7 || n2 != 14)
    FAIL ();

  strcpy (buf2 + 2, "%n%s%n");
  /* When the format string is writable and contains %n,
     with -D_FORTIFY_SOURCE=2 it causes __chk_fail.  */
  CHK_FAIL2_START
  if (printf (buf2, str4, &n1, str5, &n1) != 14)
    FAIL ();
  CHK_FAIL2_END

  /* But if there is no %n, even writable format string
     should work.  */
  buf2[6] = '\0';
  if (printf (buf2 + 4, str5) != 7)
    FAIL ();

  FILE *fp = stdout;

  /* Constant literals passed directly are always ok
     (even with warnings about possible bugs from GCC).  */
  if (fprintf (fp, "%s%n%s%n", str4, &n1, str5, &n2) != 14
      || n1 != 7 || n2 != 14)
    FAIL ();

  /* In this case the format string is not known at compile time,
     but resides in read-only memory, so is ok.  */
  if (fprintf (fp, str3, str4, &n1, str5, &n2) != 14
      || n1 != 7 || n2 != 14)
    FAIL ();

  strcpy (buf2 + 2, "%n%s%n");
  /* When the format string is writable and contains %n,
     with -D_FORTIFY_SOURCE=2 it causes __chk_fail.  */
  CHK_FAIL2_START
  if (fprintf (fp, buf2, str4, &n1, str5, &n1) != 14)
    FAIL ();
  CHK_FAIL2_END

  /* But if there is no %n, even writable format string
     should work.  */
  buf2[6] = '\0';
  if (fprintf (fp, buf2 + 4, str5) != 7)
    FAIL ();

  if (freopen (temp_filename, "r", stdin) == NULL)
    {
      puts ("could not open temporary file");
      exit (1);
    }

  if (gets (buf) != buf || memcmp (buf, "abcdefgh", 9))
    FAIL ();
  if (gets (buf) != buf || memcmp (buf, "ABCDEFGHI", 10))
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (gets (buf) != buf)
    FAIL ();
  CHK_FAIL_END
#endif

  rewind (stdin);

  if (fgets (buf, sizeof (buf), stdin) != buf
      || memcmp (buf, "abcdefgh\n", 10))
    FAIL ();
  if (fgets (buf, sizeof (buf), stdin) != buf || memcmp (buf, "ABCDEFGHI", 10))
    FAIL ();

  rewind (stdin);

  if (fgets (buf, l0 + sizeof (buf), stdin) != buf
      || memcmp (buf, "abcdefgh\n", 10))
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (fgets (buf, sizeof (buf) + 1, stdin) != buf)
    FAIL ();
  CHK_FAIL_END

  CHK_FAIL_START
  if (fgets (buf, l0 + sizeof (buf) + 1, stdin) != buf)
    FAIL ();
  CHK_FAIL_END
#endif

  rewind (stdin);

  if (fgets_unlocked (buf, sizeof (buf), stdin) != buf
      || memcmp (buf, "abcdefgh\n", 10))
    FAIL ();
  if (fgets_unlocked (buf, sizeof (buf), stdin) != buf
      || memcmp (buf, "ABCDEFGHI", 10))
    FAIL ();

  rewind (stdin);

  if (fgets_unlocked (buf, l0 + sizeof (buf), stdin) != buf
      || memcmp (buf, "abcdefgh\n", 10))
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (fgets_unlocked (buf, sizeof (buf) + 1, stdin) != buf)
    FAIL ();
  CHK_FAIL_END

  CHK_FAIL_START
  if (fgets_unlocked (buf, l0 + sizeof (buf) + 1, stdin) != buf)
    FAIL ();
  CHK_FAIL_END
#endif

  lseek (fileno (stdin), 0, SEEK_SET);

  if (read (fileno (stdin), buf, sizeof (buf) - 1) != sizeof (buf) - 1
      || memcmp (buf, "abcdefgh\n", 9))
    FAIL ();
  if (read (fileno (stdin), buf, sizeof (buf) - 1) != sizeof (buf) - 1
      || memcmp (buf, "ABCDEFGHI", 9))
    FAIL ();

  lseek (fileno (stdin), 0, SEEK_SET);

  if (read (fileno (stdin), buf, l0 + sizeof (buf) - 1) != sizeof (buf) - 1
      || memcmp (buf, "abcdefgh\n", 9))
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (read (fileno (stdin), buf, sizeof (buf) + 1) != sizeof (buf) + 1)
    FAIL ();
  CHK_FAIL_END
#endif

  if (pread (fileno (stdin), buf, sizeof (buf) - 1, sizeof (buf) - 2)
      != sizeof (buf) - 1
      || memcmp (buf, "\nABCDEFGH", 9))
    FAIL ();
  if (pread (fileno (stdin), buf, sizeof (buf) - 1, 0) != sizeof (buf) - 1
      || memcmp (buf, "abcdefgh\n", 9))
    FAIL ();
  if (pread (fileno (stdin), buf, l0 + sizeof (buf) - 1, sizeof (buf) - 3)
      != sizeof (buf) - 1
      || memcmp (buf, "h\nABCDEFG", 9))
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (pread (fileno (stdin), buf, sizeof (buf) + 1, 2 * sizeof (buf))
      != sizeof (buf) + 1)
    FAIL ();
  CHK_FAIL_END
#endif

  if (pread64 (fileno (stdin), buf, sizeof (buf) - 1, sizeof (buf) - 2)
      != sizeof (buf) - 1
      || memcmp (buf, "\nABCDEFGH", 9))
    FAIL ();
  if (pread64 (fileno (stdin), buf, sizeof (buf) - 1, 0) != sizeof (buf) - 1
      || memcmp (buf, "abcdefgh\n", 9))
    FAIL ();
  if (pread64 (fileno (stdin), buf, l0 + sizeof (buf) - 1, sizeof (buf) - 3)
      != sizeof (buf) - 1
      || memcmp (buf, "h\nABCDEFG", 9))
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (pread64 (fileno (stdin), buf, sizeof (buf) + 1, 2 * sizeof (buf))
      != sizeof (buf) + 1)
    FAIL ();
  CHK_FAIL_END
#endif

  if (freopen (temp_filename, "r", stdin) == NULL)
    {
      puts ("could not open temporary file");
      exit (1);
    }

  if (fseek (stdin, 9 + 10 + 11, SEEK_SET))
    {
      puts ("could not seek in test file");
      exit (1);
    }

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (gets (buf) != buf)
    FAIL ();
  CHK_FAIL_END
#endif

  /* Check whether missing N$ formats are detected.  */
  CHK_FAIL2_START
  printf ("%3$d\n", 1, 2, 3, 4);
  CHK_FAIL2_END

  CHK_FAIL2_START
  fprintf (stdout, "%3$d\n", 1, 2, 3, 4);
  CHK_FAIL2_END

  CHK_FAIL2_START
  sprintf (buf, "%3$d\n", 1, 2, 3, 4);
  CHK_FAIL2_END

  CHK_FAIL2_START
  snprintf (buf, sizeof (buf), "%3$d\n", 1, 2, 3, 4);
  CHK_FAIL2_END

  int sp[2];
  if (socketpair (PF_UNIX, SOCK_STREAM, 0, sp))
    FAIL ();
  else
    {
      const char *sendstr = "abcdefgh\nABCDEFGH\n0123456789\n";
      if (send (sp[0], sendstr, strlen (sendstr), 0) != strlen (sendstr))
	FAIL ();

      char recvbuf[12];
      if (recv (sp[1], recvbuf, sizeof recvbuf, MSG_PEEK)
	  != sizeof recvbuf
	  || memcmp (recvbuf, sendstr, sizeof recvbuf) != 0)
	FAIL ();

      if (recv (sp[1], recvbuf + 6, l0 + sizeof recvbuf - 7, MSG_PEEK)
	  != sizeof recvbuf - 7
	  || memcmp (recvbuf + 6, sendstr, sizeof recvbuf - 7) != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      if (recv (sp[1], recvbuf + 1, sizeof recvbuf, MSG_PEEK)
	  != sizeof recvbuf)
	FAIL ();
      CHK_FAIL_END

      CHK_FAIL_START
      if (recv (sp[1], recvbuf + 4, l0 + sizeof recvbuf - 3, MSG_PEEK)
	  != sizeof recvbuf - 3)
	FAIL ();
      CHK_FAIL_END
#endif

      socklen_t sl;
      struct sockaddr_un sa_un;

      sl = sizeof (sa_un);
      if (recvfrom (sp[1], recvbuf, sizeof recvbuf, MSG_PEEK, &sa_un, &sl)
	  != sizeof recvbuf
	  || memcmp (recvbuf, sendstr, sizeof recvbuf) != 0)
	FAIL ();

      sl = sizeof (sa_un);
      if (recvfrom (sp[1], recvbuf + 6, l0 + sizeof recvbuf - 7, MSG_PEEK,
	  &sa_un, &sl) != sizeof recvbuf - 7
	  || memcmp (recvbuf + 6, sendstr, sizeof recvbuf - 7) != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      sl = sizeof (sa_un);
      if (recvfrom (sp[1], recvbuf + 1, sizeof recvbuf, MSG_PEEK, &sa_un, &sl)
	  != sizeof recvbuf)
	FAIL ();
      CHK_FAIL_END

      CHK_FAIL_START
      sl = sizeof (sa_un);
      if (recvfrom (sp[1], recvbuf + 4, l0 + sizeof recvbuf - 3, MSG_PEEK,
	  &sa_un, &sl) != sizeof recvbuf - 3)
	FAIL ();
      CHK_FAIL_END
#endif

      close (sp[0]);
      close (sp[1]);
    }

  char fname[] = "/tmp/tst-chk1-dir-XXXXXX\0foo";
  char *enddir = strchr (fname, '\0');
  if (mkdtemp (fname) == NULL)
    {
      printf ("mkdtemp failed: %m\n");
      return 1;
    }
  *enddir = '/';
  if (symlink ("bar", fname) != 0)
    FAIL ();

  char readlinkbuf[4];
  if (readlink (fname, readlinkbuf, 4) != 3
      || memcmp (readlinkbuf, "bar", 3) != 0)
    FAIL ();
  if (readlink (fname, readlinkbuf + 1, l0 + 3) != 3
      || memcmp (readlinkbuf, "bbar", 4) != 0)
    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  if (readlink (fname, readlinkbuf + 2, l0 + 3) != 3)
    FAIL ();
  CHK_FAIL_END

  CHK_FAIL_START
  if (readlink (fname, readlinkbuf + 3, 4) != 3)
    FAIL ();
  CHK_FAIL_END
#endif

  char *cwd1 = getcwd (NULL, 0);
  if (cwd1 == NULL)
    FAIL ();

  char *cwd2 = getcwd (NULL, 250);
  if (cwd2 == NULL)
    FAIL ();

  if (cwd1 && cwd2)
    {
      if (strcmp (cwd1, cwd2) != 0)
	FAIL ();

      *enddir = '\0';
      if (chdir (fname))
	FAIL ();

      char *cwd3 = getcwd (NULL, 0);
      if (cwd3 == NULL)
	FAIL ();
      if (strcmp (fname, cwd3) != 0)
	printf ("getcwd after chdir is '%s' != '%s',"
		"get{c,}wd tests skipped\n", cwd3, fname);
      else
	{
	  char getcwdbuf[sizeof fname - 3];

	  char *cwd4 = getcwd (getcwdbuf, sizeof getcwdbuf);
	  if (cwd4 != getcwdbuf
	      || strcmp (getcwdbuf, fname) != 0)
	    FAIL ();

	  cwd4 = getcwd (getcwdbuf + 1, l0 + sizeof getcwdbuf - 1);
	  if (cwd4 != getcwdbuf + 1
	      || getcwdbuf[0] != fname[0]
	      || strcmp (getcwdbuf + 1, fname) != 0)
	    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
	  CHK_FAIL_START
	  if (getcwd (getcwdbuf + 2, l0 + sizeof getcwdbuf)
	      != getcwdbuf + 2)
	    FAIL ();
	  CHK_FAIL_END

	  CHK_FAIL_START
	  if (getcwd (getcwdbuf + 2, sizeof getcwdbuf)
	      != getcwdbuf + 2)
	    FAIL ();
	  CHK_FAIL_END
#endif

	  if (getwd (getcwdbuf) != getcwdbuf
	      || strcmp (getcwdbuf, fname) != 0)
	    FAIL ();

	  if (getwd (getcwdbuf + 1) != getcwdbuf + 1
	      || strcmp (getcwdbuf + 1, fname) != 0)
	    FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
	  CHK_FAIL_START
	  if (getwd (getcwdbuf + 2) != getcwdbuf + 2)
	    FAIL ();
	  CHK_FAIL_END
#endif
	}

      if (chdir (cwd1) != 0)
	FAIL ();
      free (cwd3);
    }

  free (cwd1);
  free (cwd2);
  *enddir = '/';
  if (unlink (fname) != 0)
    FAIL ();

  *enddir = '\0';
  if (rmdir (fname) != 0)
    FAIL ();


#if PATH_MAX > 0
  char largebuf[PATH_MAX];
  char *realres = realpath (".", largebuf);
  if (realres != largebuf)
    FAIL ();

# if __USE_FORTIFY_LEVEL >= 1
  CHK_FAIL_START
  char realbuf[1];
  realres = realpath (".", realbuf);
  if (realres != realbuf)
    FAIL ();
  CHK_FAIL_END
# endif
#endif

  if (setlocale (LC_ALL, "de_DE.UTF-8") != NULL)
    {
      assert (MB_CUR_MAX <= 10);

      /* First a simple test.  */
      char enough[10];
      if (wctomb (enough, L'A') != 1)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      /* We know the wchar_t encoding is ISO 10646.  So pick a
	 character which has a multibyte representation which does not
	 fit.  */
      CHK_FAIL_START
      char smallbuf[2];
      if (wctomb (smallbuf, L'\x100') != 2)
	FAIL ();
      CHK_FAIL_END
#endif

      mbstate_t s;
      memset (&s, '\0', sizeof (s));
      if (wcrtomb (enough, L'D', &s) != 1 || enough[0] != 'D')
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      /* We know the wchar_t encoding is ISO 10646.  So pick a
	 character which has a multibyte representation which does not
	 fit.  */
      CHK_FAIL_START
      char smallbuf[2];
      if (wcrtomb (smallbuf, L'\x100', &s) != 2)
	FAIL ();
      CHK_FAIL_END
#endif

      wchar_t wenough[10];
      memset (&s, '\0', sizeof (s));
      const char *cp = "A";
      if (mbsrtowcs (wenough, &cp, 10, &s) != 1
	  || wcscmp (wenough, L"A") != 0)
	FAIL ();

      cp = "BC";
      if (mbsrtowcs (wenough, &cp, l0 + 10, &s) != 2
	  || wcscmp (wenough, L"BC") != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      wchar_t wsmallbuf[2];
      cp = "ABC";
      mbsrtowcs (wsmallbuf, &cp, 10, &s);
      CHK_FAIL_END
#endif

      cp = "A";
      if (mbstowcs (wenough, cp, 10) != 1
	  || wcscmp (wenough, L"A") != 0)
	FAIL ();

      cp = "DEF";
      if (mbstowcs (wenough, cp, l0 + 10) != 3
	  || wcscmp (wenough, L"DEF") != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      wchar_t wsmallbuf[2];
      cp = "ABC";
      mbstowcs (wsmallbuf, cp, 10);
      CHK_FAIL_END
#endif

      memset (&s, '\0', sizeof (s));
      cp = "ABC";
      wcscpy (wenough, L"DEF");
      if (mbsnrtowcs (wenough, &cp, 1, 10, &s) != 1
	  || wcscmp (wenough, L"AEF") != 0)
	FAIL ();

      cp = "IJ";
      if (mbsnrtowcs (wenough, &cp, 1, l0 + 10, &s) != 1
	  || wcscmp (wenough, L"IEF") != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      wchar_t wsmallbuf[2];
      cp = "ABC";
      mbsnrtowcs (wsmallbuf, &cp, 3, 10, &s);
      CHK_FAIL_END
#endif

      memset (&s, '\0', sizeof (s));
      const wchar_t *wcp = L"A";
      if (wcsrtombs (enough, &wcp, 10, &s) != 1
	  || strcmp (enough, "A") != 0)
	FAIL ();

      wcp = L"BC";
      if (wcsrtombs (enough, &wcp, l0 + 10, &s) != 2
	  || strcmp (enough, "BC") != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      char smallbuf[2];
      wcp = L"ABC";
      wcsrtombs (smallbuf, &wcp, 10, &s);
      CHK_FAIL_END
#endif

      memset (enough, 'Z', sizeof (enough));
      wcp = L"EF";
      if (wcstombs (enough, wcp, 10) != 2
	  || strcmp (enough, "EF") != 0)
	FAIL ();

      wcp = L"G";
      if (wcstombs (enough, wcp, l0 + 10) != 1
	  || strcmp (enough, "G") != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      char smallbuf[2];
      wcp = L"ABC";
      wcstombs (smallbuf, wcp, 10);
      CHK_FAIL_END
#endif

      memset (&s, '\0', sizeof (s));
      wcp = L"AB";
      if (wcsnrtombs (enough, &wcp, 1, 10, &s) != 1
	  || strcmp (enough, "A") != 0)
	FAIL ();

      wcp = L"BCD";
      if (wcsnrtombs (enough, &wcp, 1, l0 + 10, &s) != 1
	  || strcmp (enough, "B") != 0)
	FAIL ();

#if __USE_FORTIFY_LEVEL >= 1
      CHK_FAIL_START
      char smallbuf[2];
      wcp = L"ABC";
      wcsnrtombs (smallbuf, &wcp, 3, 10, &s);
      CHK_FAIL_END
#endif
    }