SQLRETURN CLMoreResults( SQLHSTMT statement_handle )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
	SQLRETURN ret;

    ret = SQLMORERESULTS( cl_statement -> cl_connection,
            cl_statement -> driver_stmt );

    if ( SQL_SUCCEEDED( ret ))
    {
        SQLSMALLINT column_count;

        ret = SQLNUMRESULTCOLS( cl_statement -> cl_connection,
           cl_statement -> driver_stmt,
           &column_count );

        cl_statement -> column_count = column_count;
        cl_statement -> first_fetch_done = 0;

        if ( column_count > 0 )
        {
            ret = get_column_names( cl_statement );
        }
    }

	return ret;
}