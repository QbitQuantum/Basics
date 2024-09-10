RETCODE INSTAPI
SQLPostInstallerErrorW (DWORD fErrorCode, LPWSTR szErrorMsg)
{
  char *_errormsg_u8 = NULL;
  RETCODE retcode = SQL_ERROR;

  _errormsg_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) szErrorMsg, SQL_NTS);
  if (_errormsg_u8 == NULL && szErrorMsg)
    {
      PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
      goto done;
    }

  retcode = SQLPostInstallerError (fErrorCode, _errormsg_u8);

done:
  MEM_FREE (_errormsg_u8);

  return retcode;
}