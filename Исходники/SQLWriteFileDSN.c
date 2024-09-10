BOOL INSTAPI
SQLWriteFileDSNW (LPCWSTR lpszFileName, LPCWSTR lpszAppName,
    LPCWSTR lpszKeyName, LPWSTR lpszString)
{
  char *_filename_u8 = NULL;
  char *_appname_u8 = NULL;
  char *_keyname_u8 = NULL;
  char *_string_u8 = NULL;
  BOOL retcode = FALSE;

  _filename_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszFileName, SQL_NTS);
  if (_filename_u8 == NULL && lpszFileName)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  _appname_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszAppName, SQL_NTS);
  if (_appname_u8 == NULL && lpszAppName)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  _keyname_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszKeyName, SQL_NTS);
  if (_keyname_u8 == NULL && lpszKeyName)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  _string_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszString, SQL_NTS);
  if (_string_u8 == NULL && lpszString)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  retcode =
      SQLWriteFileDSN (_filename_u8, _appname_u8, _keyname_u8, _string_u8);

done:
  MEM_FREE (_filename_u8);
  MEM_FREE (_appname_u8);
  MEM_FREE (_keyname_u8);
  MEM_FREE (_string_u8);

  return retcode;
}