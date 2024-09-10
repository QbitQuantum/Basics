SQLRETURN SQLTablesA( SQLHSTMT statement_handle,
           SQLCHAR *catalog_name,
           SQLSMALLINT name_length1,
           SQLCHAR *schema_name,
           SQLSMALLINT name_length2,
           SQLCHAR *table_name,
           SQLSMALLINT name_length3,
           SQLCHAR *table_type,
           SQLSMALLINT name_length4 )
{
    return SQLTables( statement_handle,
           catalog_name,
           name_length1,
           schema_name,
           name_length2,
           table_name,
           name_length3,
           table_type,
           name_length4 );
}