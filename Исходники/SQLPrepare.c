SQLRETURN CLPrepare( SQLHSTMT statement_handle,
           SQLCHAR *statement_text,
           SQLINTEGER text_length )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 

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

    return SQLPREPARE( cl_statement -> cl_connection,
            cl_statement -> driver_stmt,
            statement_text,
            text_length );
}