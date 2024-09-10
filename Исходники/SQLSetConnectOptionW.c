SQLRETURN SQLSetConnectOptionW( SQLHDBC connection_handle,
           SQLUSMALLINT option,
           SQLULEN value )
{
    DMHDBC connection = (DMHDBC)connection_handle;
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ];
	SQLWCHAR buffer[ 512 ];

    /*
     * doesn't require a handle
     */

    if ( option == SQL_ATTR_TRACE )
    {
        if ((SQLLEN) value != SQL_OPT_TRACE_OFF && 
            (SQLLEN) value != SQL_OPT_TRACE_ON ) 
        {
            if ( __validate_dbc( connection ))
            {
                thread_protect( SQL_HANDLE_DBC, connection );
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY024" );
        
                __post_internal_error( &connection -> error,
                    ERROR_HY024, NULL,
                    connection -> environment -> requested_version );
        
                return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
            }
            else 
            {
                return SQL_INVALID_HANDLE;
            }
        }

        if ( value == SQL_OPT_TRACE_OFF )
        {
            log_info.log_flag = 0;
        }
        else
        {
            log_info.log_flag = 1;
        }

        return SQL_SUCCESS;
    }
    else if ( option == SQL_ATTR_TRACEFILE )
    {
        if ( value )
        {
            if (((SQLWCHAR*)value)[ 0 ] == 0 ) 
            {
                if ( __validate_dbc( connection ))
                {
                    thread_protect( SQL_HANDLE_DBC, connection );
                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            "Error: HY024" );
            
                    __post_internal_error( &connection -> error,
                        ERROR_HY024, NULL,
                        connection -> environment -> requested_version );
            
                    return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                }
                else 
                {
                    return SQL_INVALID_HANDLE;
                }
            }
            else 
            {
                if ( log_info.log_file_name )
                {
                    free( log_info.log_file_name );
                }
                log_info.log_file_name = unicode_to_ansi_alloc((SQLWCHAR *) value, SQL_NTS, connection );
            }
        }
        else 
        {
            if ( __validate_dbc( connection ))
            {
                thread_protect( SQL_HANDLE_DBC, connection );
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY009" );
        
                __post_internal_error( &connection -> error,
                    ERROR_HY009, NULL,
                    connection -> environment -> requested_version );
        
                return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
            }
            else 
            {
                return SQL_INVALID_HANDLE;
            }
        }
        return SQL_SUCCESS;
    }

    /*
     * check connection
     */

    if ( !__validate_dbc( connection ))
    {
        dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: SQL_INVALID_HANDLE" );

#ifdef WITH_HANDLE_REDIRECT
		{
			DMHDBC parent_connection;

			parent_connection = find_parent_handle( connection, SQL_HANDLE_DBC );

			if ( parent_connection ) {
        		dm_log_write( __FILE__, 
                	__LINE__, 
                    	LOG_INFO, 
                    	LOG_INFO, 
                    	"Info: found parent handle" );

				if ( CHECK_SQLSETCONNECTOPTIONW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLSETCONNECTOPTIONW( parent_connection, 
							connection_handle, 
							option,
							value );
				}
			}
		}
#endif
        return SQL_INVALID_HANDLE;
    }

    function_entry( connection );

    if ( log_info.log_flag )
    {
        sprintf( connection -> msg, "\n\t\tEntry:\
\n\t\t\tConnection = %p\
\n\t\t\tOption = %s\
\n\t\t\tValue = %d",
                connection,
                __con_attr_as_string( s1, option ),
                (int)value );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
    }