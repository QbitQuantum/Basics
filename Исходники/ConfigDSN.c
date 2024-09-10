BOOL INSTAPI ConfigDSN(HWND hWnd, WORD nRequest, LPCSTR pszDriverA,
                       LPCSTR pszAttributesA)
{
  BOOL rc;

  size_t lenDriver = strlen(pszDriverA);
  size_t lenAttrib = strlen(pszAttributesA);

  /* We will assume using one-byte Latin string as a subset of UTF-8 */
  SQLWCHAR *pszDriverW= (SQLWCHAR *) myodbc_malloc((lenDriver + 1) * 
                                                sizeof(SQLWCHAR), MYF(0));
  SQLWCHAR *pszAttributesW= (SQLWCHAR *)myodbc_malloc((lenAttrib + 1) * 
                                                  sizeof(SQLWCHAR), MYF(0));

  utf8_as_sqlwchar(pszDriverW, lenDriver, (SQLCHAR* )pszDriverA, lenDriver);
  utf8_as_sqlwchar(pszAttributesW, lenAttrib, (SQLCHAR* )pszAttributesA, 
                   lenAttrib);

  rc= ConfigDSNW(hWnd, nRequest, pszDriverW, pszAttributesW);

  x_free(pszDriverW);
  x_free(pszAttributesW);                 
  return rc;
}