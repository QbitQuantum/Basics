SQLRETURN SQLGetConnectOptionW( SQLHDBC connection_handle,
           SQLUSMALLINT option,
           SQLPOINTER value )
{
    DMHDBC connection = (DMHDBC)connection_handle;
    int type = 0;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ];

    /*
     * doesn't require a handle
     */

    if ( option == SQL_ATTR_TRACE )
    {
        if ( value )
        {
            if ( log_info.log_flag )
            {
                *((SQLINTEGER*)value) = SQL_OPT_TRACE_ON;
            }
            else
            {
                *((SQLINTEGER*)value) = SQL_OPT_TRACE_ON;
            }
        }

        return SQL_SUCCESS;
    }
    else if ( option == SQL_ATTR_TRACEFILE )
    {
        SQLRETURN ret =  SQL_SUCCESS;

        if ( log_info.log_file_name )
        {
            ansi_to_unicode_copy( value, log_info.log_file_name, SQL_NTS, connection );
        }
        else
        {
            ansi_to_unicode_copy( value, "", SQL_NTS, connection );
        }
        return ret;
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

				if ( CHECK_SQLGETCONNECTOPTIONW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLGETCONNECTOPTIONW( parent_connection, 
							connection,
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
\n\t\t\tValue = %p",
                connection,
                __con_attr_as_string( s1, option ),
                value );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
    }