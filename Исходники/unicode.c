/************************************************************************
* name: SQLTablePrivilegesW
* arguments:
* returns/side-effects:
* description:
* NOTE:
************************************************************************/
ODBC_INTERFACE RETCODE SQL_API
SQLTablePrivilegesW (SQLHSTMT hstmt,
                     SQLWCHAR *catalog, SQLSMALLINT catalog_len,
                     SQLWCHAR *schema, SQLSMALLINT schema_len,
                     SQLWCHAR *table, SQLSMALLINT table_len)
{
  RETCODE ret = ODBC_ERROR;
  SQLCHAR *cb_catalog = NULL,  *cb_schema = NULL, *cb_table = NULL;
  int cb_catalog_len = 0, cb_schema_len = 0, cb_table_len = 0;
  
  OutputDebugString ("SQLTablePrivilegesW called.\n");
  wide_char_to_bytes (catalog, catalog_len, &cb_catalog, &cb_catalog_len, NULL);
  wide_char_to_bytes (schema, schema_len, &cb_schema, &cb_schema_len, NULL);
  wide_char_to_bytes (table, table_len, &cb_table, &cb_table_len, NULL);
  
  ret = SQLTablePrivileges(hstmt, 
                                           cb_catalog, cb_catalog_len, 
                                           cb_schema, cb_schema_len, 
                                           cb_table, cb_table_len);
  
  UT_FREE(cb_catalog);
  UT_FREE(cb_schema);
  UT_FREE(cb_table);
  return ret;
}