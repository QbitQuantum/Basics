NS_IMETHODIMP
mozSqlConnectionODBC::Init(const nsAString &aHost, PRInt32 aPort,
                           const nsAString &aDatabase, const nsAString &aUsername,
                           const nsAString &aPassword)
{
  if (mConnection)
    return NS_OK;

  SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &mEnv);
  SQLSetEnvAttr(mEnv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
  SQLAllocHandle(SQL_HANDLE_DBC, mEnv, &mConnection);

  NS_LossyConvertUTF16toASCII inString(NS_LITERAL_STRING("DSN=") + aDatabase +
                                       NS_LITERAL_STRING(";UID=") + aUsername +
                                       NS_LITERAL_STRING(";PWD=") + aPassword);
  char outString[1024];
  SQLSMALLINT outStringLength;
  if (!SQL_SUCCEEDED(SQLDriverConnect(mConnection, NULL,
                                      (SQLCHAR*)inString.get(),
                                      inString.Length(),
                                      (SQLCHAR*)outString, sizeof(outString),
                                      &outStringLength,
                                      SQL_DRIVER_COMPLETE))) {
    SetError(mConnection, SQL_HANDLE_DBC);

    return NS_ERROR_FAILURE;
  }

  return NS_OK;
}