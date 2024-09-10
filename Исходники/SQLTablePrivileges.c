SQLRETURN SQLTablePrivilegesA(
    SQLHSTMT           statement_handle,
    SQLCHAR            *sz_catalog_name,
    SQLSMALLINT        cb_catalog_name,
    SQLCHAR            *sz_schema_name,
    SQLSMALLINT        cb_schema_name,
    SQLCHAR            *sz_table_name,
    SQLSMALLINT        cb_table_name )
{
    return SQLTablePrivileges( statement_handle,
                    sz_catalog_name,
                    cb_catalog_name,
                    sz_schema_name,
                    cb_schema_name,
                    sz_table_name,
                    cb_table_name );
}