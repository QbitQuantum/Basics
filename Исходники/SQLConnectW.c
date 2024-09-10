SQLRETURN SQLConnectW( SQLHDBC connection_handle,
           SQLWCHAR *server_name,
           SQLSMALLINT name_length1,
           SQLWCHAR *user_name,
           SQLSMALLINT name_length2,
           SQLWCHAR *authentication,
           SQLSMALLINT name_length3 )
{
    DMHDBC connection = (DMHDBC)connection_handle;
    int len, ret_from_connect;
    SQLWCHAR dsn[ SQL_MAX_DSN_LENGTH + 1 ];
    char lib_name[ INI_MAX_PROPERTY_VALUE + 1 ];
    char driver_name[ INI_MAX_PROPERTY_VALUE + 1 ];
    SQLCHAR ansi_dsn[ SQL_MAX_DSN_LENGTH + 1 ];
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ], s2[ 100 + LOG_MESSAGE_LEN ], s3[ 100 + LOG_MESSAGE_LEN ], ansi_user[ SQL_MAX_DSN_LENGTH + 1 ], ansi_pwd[ SQL_MAX_DSN_LENGTH + 1 ];
    int warnings;

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

				if ( CHECK_SQLCONNECTW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLCONNECTW( parent_connection, 
							connection_handle, 
							server_name, 
							name_length1,
							user_name,
							name_length2,
							authentication,
							name_length3 );
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
\n\t\t\tServer Name = %s\
\n\t\t\tUser Name = %s\
\n\t\t\tAuthentication = %s",
                connection,
                __wstring_with_length( s1, server_name, name_length1 ),
                __wstring_with_length( s2, user_name, name_length2 ),
                __wstring_with_length_pass( s3, authentication, name_length3 ));

        dm_log_write( __FILE__,
                __LINE__,
                LOG_INFO,
                LOG_INFO,
                connection -> msg );
    }