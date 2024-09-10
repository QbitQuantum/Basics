BOOL INSTAPI
SQLInstallODBCW (HWND hwndParent, LPCWSTR lpszInfFile, LPCWSTR lpszSrcPath,
    LPCWSTR lpszDrivers)
{
  char *_inf_u8 = NULL;
  char *_srcpath_u8 = NULL;
  char *_drivers_u8 = NULL;
  BOOL retcode = FALSE;

  _inf_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszInfFile, SQL_NTS);
  if (_inf_u8 == NULL && lpszInfFile)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  _srcpath_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszSrcPath, SQL_NTS);
  if (_srcpath_u8 == NULL && lpszSrcPath)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  _drivers_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszDrivers, SQL_NTS);
  if (_drivers_u8 == NULL && lpszDrivers)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  retcode = SQLInstallODBC (hwndParent, _inf_u8, _srcpath_u8, _drivers_u8);

done:
  MEM_FREE (_inf_u8);
  MEM_FREE (_srcpath_u8);
  MEM_FREE (_drivers_u8);

  return retcode;
}