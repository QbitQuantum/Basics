void test_mbs(void) {
  wchar_t wstr1[256] = {
                         L'e',
                         0xE8, // latin small letter e with grave
                         0xE9, // latin small letter e with acute
                         L'a',
                         0xE0, // latin small letter a with grave
                         0x20AC, // euro sign
                         L'b',
                         0 };
  wchar_t wstr2[256];
  char    astr[256];
  extern int global_use_utf16_conversion;

  global_use_utf16_conversion = 1;

  size_t len1 = wcslen(wstr1);

  printf("wstr1 - %d - '%ls'\n",(int)len1,wstr1);

  size_t len0 = wcstombs(astr,wstr1,sizeof(astr));
  printf("astr - %d - '%s'\n",(int)len0,astr);

  size_t len2 = mbstowcs(wstr2,astr,sizeof(wstr2)/sizeof(*wstr2));
  printf("wstr - %d - '%ls'\n",(int)len2,wstr2);

  if (wcscmp(wstr1,wstr2) != 0) {
    printf("ERROR during conversions wcs -> mbs -> wcs\n");
    exit(EXIT_FAILURE);
  }

  char *ptr = astr;
  size_t len = 0;
  while (*ptr) {
    ptr = CharNextA(ptr);
    len += 1;
  }
  if (len != len1) {
    printf("ERROR CharNextA : len=%d, len1=%d\n",(int)len,(int)len1);
    exit(EXIT_FAILURE);
  }

  UString ustr(wstr1);
  assert(ustr.Length() == (int)len1);

  AString  ansistr(astr);
  assert(ansistr.Length() == (int)len0);

  ansistr = UnicodeStringToMultiByte(ustr);
  assert(ansistr.Length() == (int)len0);

  assert(strcmp(ansistr,astr) == 0);
  assert(wcscmp(ustr,wstr1) == 0);

  UString ustr2 = MultiByteToUnicodeString(astr);
  assert(ustr2.Length() == (int)len1);
  assert(wcscmp(ustr2,wstr1) == 0);
}