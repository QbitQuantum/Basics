SQLRETURN SQLExecDirectW( SQLHSTMT statement_handle,
           SQLWCHAR *statement_text,
           SQLINTEGER text_length )
{
    DMHSTMT statement = (DMHSTMT) statement_handle;
    SQLRETURN ret;
    SQLCHAR *s1;
    SQLCHAR s2[ 100 + LOG_MESSAGE_LEN ];

    /*
     * check statement
     */

    if ( !__validate_stmt( statement ))
    {
        dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: SQL_INVALID_HANDLE" );

#ifdef WITH_HANDLE_REDIRECT
		{
			DMHSTMT parent_statement;

			parent_statement = find_parent_handle( statement, SQL_HANDLE_STMT );

			if ( parent_statement ) {
        		dm_log_write( __FILE__, 
                	__LINE__, 
                    	LOG_INFO, 
                    	LOG_INFO, 
                    	"Info: found parent handle" );

				if ( CHECK_SQLEXECDIRECTW( parent_statement -> connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

                	return  SQLEXECDIRECTW( parent_statement -> connection,
							statement,
							statement_text,
							text_length );
				}
			}
		}
#endif
        return SQL_INVALID_HANDLE;
    }

    function_entry( statement );

    if ( log_info.log_flag )
    {
        /*
         * allocate some space for the buffer
         */

        if ( statement_text && text_length == SQL_NTS )
        {
             s1 = malloc( wide_strlen( statement_text ) * 2 + LOG_MESSAGE_LEN * 2 );
        }
        else if ( statement_text )
        {
            s1 = malloc( text_length + LOG_MESSAGE_LEN * 2 );
        }
        else
        {
            s1 = malloc( LOG_MESSAGE_LEN * 2 );
        }

        sprintf( statement -> msg, "\n\t\tEntry:\
\n\t\t\tStatement = %p\
\n\t\t\tSQL = %s",
                statement,
                __wstring_with_length( s1, statement_text, text_length ));

        free( s1 );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                statement -> msg );
    }

    thread_protect( SQL_HANDLE_STMT, statement );

    if ( !statement_text )
    {
        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                "Error: HY009" );

        __post_internal_error( &statement -> error,
                ERROR_HY009, NULL,
                statement -> connection -> environment -> requested_version );

        return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
    }

    if ( text_length <= 0 && text_length != SQL_NTS )
    {
        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                "Error: HY090" );

        __post_internal_error( &statement -> error,
                ERROR_HY090, NULL,
                statement -> connection -> environment -> requested_version );

        return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
    }

    /*
     * check states
     */

#ifdef NR_PROBE
    if ( statement -> state == STATE_S5 ||
            statement -> state == STATE_S6 ||
            statement -> state == STATE_S7 )
#else
    if (( statement -> state == STATE_S6 && statement -> eod == 0 ) ||
            statement -> state == STATE_S7 )
#endif
    {
        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                "Error: 24000" );

        __post_internal_error( &statement -> error,
                ERROR_24000, NULL,
                statement -> connection -> environment -> requested_version );

        return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
    }
    else if ( statement -> state == STATE_S8 ||
            statement -> state == STATE_S9 ||
            statement -> state == STATE_S10 )
    {
        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                "Error: HY010" );

        __post_internal_error( &statement -> error,
                ERROR_HY010, NULL,
                statement -> connection -> environment -> requested_version );

        return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
    }

    if ( statement -> state == STATE_S11 ||
            statement -> state == STATE_S12 )
    {
        if ( statement -> interupted_func != SQL_API_SQLEXECDIRECT )
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: HY010" );

            __post_internal_error( &statement -> error,
                    ERROR_HY010, NULL,
                    statement -> connection -> environment -> requested_version );

            return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
        }
    }

    if ( statement -> connection -> unicode_driver ||
		    CHECK_SQLEXECDIRECTW( statement -> connection ))
    {
#ifdef NR_PROBE
        if ( !CHECK_SQLEXECDIRECTW( statement -> connection ) ||
                !CHECK_SQLNUMRESULTCOLS( statement -> connection ))
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: IM001" );

            __post_internal_error( &statement -> error,
                    ERROR_IM001, NULL,
                    statement -> connection -> environment -> requested_version );

            return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
        }
#else
        if ( !CHECK_SQLEXECDIRECTW( statement -> connection ))
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: IM001" );

            __post_internal_error( &statement -> error,
                    ERROR_IM001, NULL,
                    statement -> connection -> environment -> requested_version );

            return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
        }
#endif

        ret = SQLEXECDIRECTW( statement -> connection,
                statement -> driver_stmt,
                statement_text,
                text_length );
    }
    else
    {
        SQLCHAR *as1 = NULL;
        int clen;

#ifdef NR_PROBE
        if ( !CHECK_SQLEXECDIRECT( statement -> connection ) ||
                !CHECK_SQLNUMRESULTCOLS( statement -> connection ))
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: IM001" );

            __post_internal_error( &statement -> error,
                    ERROR_IM001, NULL,
                    statement -> connection -> environment -> requested_version );

            return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
        }
#else
        if ( !CHECK_SQLEXECDIRECT( statement -> connection ))
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: IM001" );

            __post_internal_error( &statement -> error,
                    ERROR_IM001, NULL,
                    statement -> connection -> environment -> requested_version );

            return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
        }
#endif

        as1 = (SQLCHAR*) unicode_to_ansi_alloc( statement_text, text_length, statement -> connection, &clen );

        text_length = clen;

        ret = SQLEXECDIRECT( statement -> connection,
                statement -> driver_stmt,
                as1,
                text_length );

        if ( as1 )
            free( as1 );
    }

    if ( SQL_SUCCEEDED( ret ))
    {
#ifdef NR_PROBE
        SQLRETURN local_ret;
  
        /*
         * grab any errors
         */

        if ( ret == SQL_SUCCESS_WITH_INFO )
        {
            function_return_ex( IGNORE_THREAD, statement, ret, TRUE );
        }

        local_ret = SQLNUMRESULTCOLS( statement -> connection,
                statement -> driver_stmt, &statement -> numcols );

        if ( statement -> numcols > 0 )
        {
            statement -> state = STATE_S5;
        }
        else
        {
            statement -> state = STATE_S4;
        }
#else
        /*
         * We don't know for sure
         */
        statement -> hascols = 1;
        statement -> state = STATE_S5;
#endif

        statement -> prepared = 0;

        /*
         * there is a issue here with transactions, but for the
         * moment
         *
        statement -> connection -> state = STATE_C6;
         */
    }
    else if ( ret == SQL_NEED_DATA )
    {
        statement -> interupted_func = SQL_API_SQLEXECDIRECT;
        statement -> interupted_state = statement -> state;
        statement -> state = STATE_S8;

        statement -> prepared = 0;
    }
    else if ( ret == SQL_PARAM_DATA_AVAILABLE )
    {
        statement -> interupted_func = SQL_API_SQLEXECDIRECT;
        statement -> interupted_state = statement -> state;
        statement -> state = STATE_S13;
    }
    else if ( ret == SQL_STILL_EXECUTING )
    {
        statement -> interupted_func = SQL_API_SQLEXECDIRECT;
        if ( statement -> state != STATE_S11 &&
                statement -> state != STATE_S12 )
            statement -> state = STATE_S11;

        statement -> prepared = 0;
    }
    else
    {
        statement -> state = STATE_S1;
    }

    if ( log_info.log_flag )
    {
        sprintf( statement -> msg, 
                "\n\t\tExit:[%s]",
                    __get_return_status( ret, s2 ));

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                statement -> msg );
    }

    return function_return( SQL_HANDLE_STMT, statement, ret );
}