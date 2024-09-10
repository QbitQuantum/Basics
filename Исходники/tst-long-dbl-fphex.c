static int
do_test (void)
{
#ifndef NO_LONG_DOUBLE
  int result = 0;
  const long double x = 24.5;
  wchar_t a[16];
  swprintf (a, sizeof a / sizeof a[0], L"%La\n", x);
  wchar_t A[16];
  swprintf (A, sizeof A / sizeof A[0], L"%LA\n", x);

  /* Here wprintf can return four valid variants.  We must accept all
     of them.  */
  result |= (wmemcmp (a, L"0xc.4p+1", 8) == 0
	     && wmemcmp (A, L"0XC.4P+1", 8) == 0);
  result |= (wmemcmp (a, L"0x3.1p+3", 8) == 0
	     && wmemcmp (A, L"0X3.1P+3", 8) == 0);
  result |= (wmemcmp (a, L"0x6.2p+2", 8) == 0
	     && wmemcmp (A, L"0X6.2P+2", 8) == 0);
  result |= (wmemcmp (a, L"0x1.88p+4", 8) == 0
	     && wmemcmp (A, L"0X1.88P+4", 8) == 0);

  return result != 1;
#else
  return 0;
#endif
}