SQLRETURN SQLProceduresA(
    SQLHSTMT           statement_handle,
    SQLCHAR            *sz_catalog_name,
    SQLSMALLINT        cb_catalog_name,
    SQLCHAR            *sz_schema_name,
    SQLSMALLINT        cb_schema_name,
    SQLCHAR            *sz_proc_name,
    SQLSMALLINT        cb_proc_name )
{
    return SQLProcedures( statement_handle,
                sz_catalog_name,
                cb_catalog_name,
                sz_schema_name,
                cb_schema_name,
                sz_proc_name,
                cb_proc_name );
}