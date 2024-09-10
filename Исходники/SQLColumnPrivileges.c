SQLRETURN CLColumnPrivileges(
    SQLHSTMT            statement_handle,
    SQLCHAR             *catalog_name,
    SQLSMALLINT         name_length1,
    SQLCHAR             *schema_name,
    SQLSMALLINT         name_length2,
    SQLCHAR             *table_name,
    SQLSMALLINT         name_length3,
    SQLCHAR             *column_name,
    SQLSMALLINT         name_length4 )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
    SQLRETURN ret;

    ret = SQLCOLUMNPRIVILEGES( cl_statement -> cl_connection,
            cl_statement -> driver_stmt,
            catalog_name,
            name_length1,
            schema_name,
            name_length2,
            table_name,
            name_length3,
            column_name,
            name_length4 );

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