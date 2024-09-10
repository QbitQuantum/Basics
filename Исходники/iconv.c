int fputsU(const char *buf, FILE *f) { /* fputs a UTF-8 string */
  int n;

  if (!codePage) codePage = GetConsoleOutputCP();
  if (codePage != CP_UTF8) n = ConvertString(buf, strlen(buf)+1, CP_UTF8, codePage, NULL);
  if (n > 0) { /* If no error, and something to output */
    int iErr = fputs(buf, f);
    if ((iErr >= 0) && DEBUG_IS_ON()) fflush(f); /* Slower, but ensures we get everything before crashes! */
    if (iErr < 0) n = iErr;
  }
  return n; /* Return the error (n<0) or success (n>=0) */
}