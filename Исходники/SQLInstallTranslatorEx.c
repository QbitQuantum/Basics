BOOL INSTAPI
SQLInstallTranslatorExW (LPCWSTR lpszTranslator, LPCWSTR lpszPathIn,
    LPWSTR lpszPathOut, WORD cbPathOutMax, WORD * pcbPathOut, WORD fRequest,
    LPDWORD lpdwUsageCount)
{
  char *_translator_u8 = NULL;
  char *_pathin_u8 = NULL;
  char *_pathout_u8 = NULL;
  BOOL retcode = FALSE;
  int length;
  SQLWCHAR *ptr;
  char *ptr_u8;

  for (length = 0, ptr = (SQLWCHAR *) lpszTranslator; *ptr;
      length += WCSLEN (ptr) + 1, ptr += WCSLEN (ptr) + 1);

  if (length > 0)
    {
      if ((_translator_u8 = malloc (length * UTF8_MAX_CHAR_LEN + 1)) != NULL)
	{
	  for (ptr = (SQLWCHAR *) lpszTranslator, ptr_u8 = _translator_u8;
	      *ptr; ptr += WCSLEN (ptr) + 1, ptr_u8 += STRLEN (ptr_u8) + 1)
	    dm_StrCopyOut2_W2A (ptr, ptr_u8, WCSLEN (ptr) * UTF8_MAX_CHAR_LEN,
		NULL);
	  *ptr_u8 = '\0';
	}
    }
  else
    _translator_u8 =
	(char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszTranslator, SQL_NTS);

  if (_translator_u8 == NULL && lpszTranslator)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  _pathin_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszPathIn, SQL_NTS);
  if (_pathin_u8 == NULL && lpszPathIn)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  if (cbPathOutMax > 0)
    {
      if ((_pathout_u8 =
	      malloc (cbPathOutMax * UTF8_MAX_CHAR_LEN + 1)) == NULL)
	{
	  PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
	  goto done;
	}
    }

  retcode = SQLInstallTranslatorEx (_translator_u8, _pathin_u8,
      _pathout_u8, cbPathOutMax * UTF8_MAX_CHAR_LEN, pcbPathOut, fRequest,
      lpdwUsageCount);

  if (retcode == TRUE)
    {
      dm_StrCopyOut2_U8toW (_pathout_u8, lpszPathOut, cbPathOutMax,
	  pcbPathOut);
    }

done:
  MEM_FREE (_translator_u8);
  MEM_FREE (_pathin_u8);
  MEM_FREE (_pathout_u8);

  return retcode;
}