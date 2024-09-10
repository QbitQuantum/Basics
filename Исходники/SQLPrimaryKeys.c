SQLRETURN CLPrimaryKeys(
    SQLHSTMT           statement_handle,
    SQLCHAR            *sz_catalog_name,
    SQLSMALLINT        cb_catalog_name,
    SQLCHAR            *sz_schema_name,
    SQLSMALLINT        cb_schema_name,
    SQLCHAR            *sz_table_name,
    SQLSMALLINT        cb_table_name )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
    SQLRETURN ret;

    ret = SQLPRIMARYKEYS( cl_statement -> cl_connection,
            cl_statement -> driver_stmt,
            sz_catalog_name,
            cb_catalog_name,
            sz_schema_name,
            cb_schema_name,
            sz_table_name,
            cb_table_name );

    if ( SQL_SUCCEEDED( ret ))
    {
        SQLSMALLINT column_count;

        ret = SQLNUMRESULTCOLS( cl_statement -> cl_connection,
           cl_statement -> driver_stmt,
           &column_count );

        cl_statement -> column_count = column_count;
        cl_statement -> first_fetch_done = 0;
        cl_statement -> not_from_select = 1;

        if ( column_count > 0 )
        {
            ret = get_column_names( cl_statement );
        }
    }
    return ret;
}