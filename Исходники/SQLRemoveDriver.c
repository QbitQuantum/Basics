BOOL INSTAPI
SQLRemoveDriverW (LPCWSTR lpszDriver, BOOL fRemoveDSN, LPDWORD lpdwUsageCount)
{
  char *_driver_u8 = NULL;
  BOOL retcode = FALSE;

  _driver_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszDriver, SQL_NTS);
  if (_driver_u8 == NULL && lpszDriver)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  retcode = SQLRemoveDriver (_driver_u8, fRemoveDSN, lpdwUsageCount);

done:
  MEM_FREE (_driver_u8);

  return retcode;
}