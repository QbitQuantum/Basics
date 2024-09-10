SQLRETURN SQLColumnsA( SQLHSTMT statement_handle,
           SQLCHAR *catalog_name,
           SQLSMALLINT name_length1,
           SQLCHAR *schema_name,
           SQLSMALLINT name_length2,
           SQLCHAR *table_name,
           SQLSMALLINT name_length3,
           SQLCHAR *column_name,
           SQLSMALLINT name_length4 )
{
    return SQLColumns( statement_handle,
            catalog_name,
            name_length1,
            schema_name,
            name_length2,
            table_name,
            name_length3,
            column_name,
            name_length4 );
}