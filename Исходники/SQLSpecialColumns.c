SQLRETURN SQLSpecialColumnsA( SQLHSTMT statement_handle,
           SQLUSMALLINT identifier_type,
           SQLCHAR *catalog_name,
           SQLSMALLINT name_length1,
           SQLCHAR *schema_name,
           SQLSMALLINT name_length2,
           SQLCHAR *table_name,
           SQLSMALLINT name_length3,
           SQLUSMALLINT scope,
           SQLUSMALLINT nullable )
{
    return SQLSpecialColumns( statement_handle,
           identifier_type,
           catalog_name,
           name_length1,
           schema_name,
           name_length2,
           table_name,
           name_length3,
           scope,
           nullable );
}