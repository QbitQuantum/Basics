BOOL INSTAPI
SQLRemoveDefaultDataSource (void)
{
  return SQLConfigDataSource (NULL, ODBC_REMOVE_DEFAULT_DSN, NULL, NULL);
}