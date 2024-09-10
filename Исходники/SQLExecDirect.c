SQLRETURN CLExecDirect( SQLHSTMT statement_handle,
           SQLCHAR *statement_text,
           SQLINTEGER text_length )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
    SQLRETURN ret;

    /*
     * save the statement for later use
     */

    if ( cl_statement -> sql_text )
    {
        free( cl_statement -> sql_text );
    }
    if ( text_length < 0 )
    {
        cl_statement -> sql_text = strdup((char*) statement_text );
    }
    else
    {
        cl_statement -> sql_text = malloc( text_length + 1 );
        memcpy( cl_statement -> sql_text, statement_text, text_length );
        cl_statement -> sql_text[ text_length ] = '\0';
    }

    ret = SQLEXECDIRECT( cl_statement -> cl_connection,
           cl_statement -> driver_stmt,
           statement_text,
           text_length );

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