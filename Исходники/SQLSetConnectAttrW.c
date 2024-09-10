SQLRETURN SQLSetConnectAttrW( SQLHDBC connection_handle,
           SQLINTEGER attribute,
           SQLPOINTER value,
           SQLINTEGER string_length )
{
    DMHDBC connection = (DMHDBC)connection_handle;
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ];
	SQLWCHAR buffer[ 512 ];

    /*
     * doesn't require a handle
     */

    if ( attribute == SQL_ATTR_TRACE )
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

        if ((SQLLEN) value == SQL_OPT_TRACE_OFF )
        {
            char force_string[ 30 ];

            SQLGetPrivateProfileString( "ODBC", "ForceTrace", "0",
				force_string, sizeof( force_string ), 
                "ODBCINST.INI" );

            if ( force_string[ 0 ] == '1' ||
                toupper( force_string[ 0 ] ) == 'Y' ||
                ( toupper( force_string[ 0 ] ) == 'O' &&
                    toupper( force_string[ 1 ] ) == 'N' ))
            {
                if ( log_info.log_flag )
                {
                    dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Application tried to turn logging off" );
                }
            }
            else
            {
                if ( log_info.log_flag )
                {
                    dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Application turning logging off" );
                }
                log_info.log_flag = 0;
            }
        }
        else
        {
            log_info.log_flag = 1;
        }

        return SQL_SUCCESS;
    }
    else if ( attribute == SQL_ATTR_TRACEFILE )
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

				if ( CHECK_SQLSETCONNECTATTRW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLSETCONNECTATTRW( parent_connection, 
							connection_handle, 
           					attribute,
           					value,
           					string_length );
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
\n\t\t\tAttribute = %s\
\n\t\t\tValue = %p\
\n\t\t\tStrLen = %d",
                connection,
                __con_attr_as_string( s1, attribute ),
                value, 
                (int)string_length );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
    }