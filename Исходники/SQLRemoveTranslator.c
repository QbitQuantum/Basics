BOOL INSTAPI
SQLRemoveTranslatorW (LPCWSTR lpszTranslator, LPDWORD lpdwUsageCount)
{
  char *_translator_u8 = NULL;
  BOOL retcode = FALSE;

  _translator_u8 =
      (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszTranslator, SQL_NTS);
  if (_translator_u8 == NULL && lpszTranslator)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  retcode = SQLRemoveTranslator (_translator_u8, lpdwUsageCount);

done:
  MEM_FREE (_translator_u8);

  return retcode;
}