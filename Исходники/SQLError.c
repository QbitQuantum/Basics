SQLRETURN CLError( SQLHENV environment_handle,
           SQLHDBC connection_handle,
           SQLHSTMT statement_handle,
           SQLCHAR *sqlstate,
           SQLINTEGER *native_error,
           SQLCHAR *message_text,
           SQLSMALLINT buffer_length,
           SQLSMALLINT *text_length )
{
    if ( statement_handle )
    {
        CLHSTMT cl_statement = (CLHSTMT) statement_handle; 

		if ( cl_statement -> driver_stmt_closed ) 
		{
			return SQL_NO_DATA;
		}

        if ( CHECK_SQLERROR( cl_statement -> cl_connection ))
        {
            return SQLERROR( cl_statement -> cl_connection,
               SQL_NULL_HENV,
               SQL_NULL_HDBC,
               cl_statement -> driver_stmt,
               sqlstate,
               native_error,
               message_text,
               buffer_length,
               text_length );
        }
        else
        {
            SQLRETURN ret;

            ret = SQLGETDIAGREC( cl_statement -> cl_connection,
               SQL_HANDLE_STMT,
               cl_statement -> driver_stmt,
               cl_statement -> error_count,
               sqlstate,
               native_error,
               message_text,
               buffer_length,
               text_length );

            if ( SQL_SUCCEEDED( ret ))
            {
               cl_statement -> error_count ++;
            }
            else
            {
               cl_statement -> error_count = 0;
            }

            return ret;
        }
    }
    else if ( connection_handle )
    {
        CLHDBC cl_connection = (CLHDBC) connection_handle; 

        if ( CHECK_SQLERROR( cl_connection ))
        {
            return SQLERROR( cl_connection,
               SQL_NULL_HENV,
               cl_connection -> driver_dbc,
               SQL_NULL_HSTMT,
               sqlstate,
               native_error,
               message_text,
               buffer_length,
               text_length );
        }
        else
        {
            SQLRETURN ret;

            ret = SQLGETDIAGREC( cl_connection,
               SQL_HANDLE_DBC,
               cl_connection -> driver_dbc,
               cl_connection -> error_count,
               sqlstate,
               native_error,
               message_text,
               buffer_length,
               text_length );

            if ( SQL_SUCCEEDED( ret ))
            {
               cl_connection -> error_count ++;
            }
            else
            {
               cl_connection -> error_count = 0;
            }

            return ret;
        }
    }
    else if ( environment_handle )
    {
        /*
         * shouldn't get here
         */

        return SQL_NO_DATA;
    }
}