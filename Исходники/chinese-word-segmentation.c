char* getstr () {
  wchar_t *str;
  char *ret;
  wint_t i = 1;
  size_t j;
  /* assuming a sentence contains at most 200 wide characters */
  size_t WCHAR_MAX_SIZE = sizeof (wchar_t) * 200;

  str = (wchar_t *) malloc (WCHAR_MAX_SIZE);
  while ('\n' != (str[i - 1] = getwchar ())) {
    if (str[i - 1] == WEOF) break;
    i ++;
  }
  str[i - 1] = L'\0';
  j = MB_CUR_MAX * (wcslen (str) + 1);
  ret = (char *) malloc (j);
  wcstombs (ret, str, j);
  ret[j - 1] = '\0';
  free (str);
  return ret;
}