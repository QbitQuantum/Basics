SQLRETURN SQL_API
SQLDriverConnectW (
    SQLHDBC hdbc,
    HWND hwnd,
    SQLWCHAR * wszConnStrIn,
    SQLSMALLINT cbConnStrIn,
    SQLWCHAR * wszConnStrOut,
    SQLSMALLINT cbConnStrOut,
    SQLSMALLINT * pcbConnStrOut,
    SQLUSMALLINT fDriverCompletion)
{
  SQLRETURN rc;
  long len;
  wcharset_t *charset = NULL;
  DEFINE_INPUT_NARROW (ConnStrIn);
  DEFINE_OUTPUT_CHAR_NARROW_N (ConnStrOut);

  MAKE_INPUT_NARROW_N (ConnStrIn);
  MAKE_OUTPUT_CHAR_NARROW_N (ConnStrOut);

  rc = SQLDriverConnect (hdbc, hwnd, szConnStrIn, cbConnStrIn, szConnStrOut, cbConnStrOut, pcbConnStrOut, fDriverCompletion);

  FREE_INPUT_NARROW (ConnStrIn);
  SET_AND_FREE_OUTPUT_CHAR_NARROW_N (ConnStrOut);

  return rc;
}