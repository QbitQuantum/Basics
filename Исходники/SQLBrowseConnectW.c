SQLRETURN SQLBrowseConnectW(
    SQLHDBC            hdbc,
    SQLWCHAR           *conn_str_in,
    SQLSMALLINT        len_conn_str_in,
    SQLWCHAR           *conn_str_out,
    SQLSMALLINT        conn_str_out_max,
    SQLSMALLINT        *ptr_conn_str_out )
{
    DMHDBC connection = (DMHDBC) hdbc;
    struct con_struct con_struct;
    char *driver, *dsn;
    char lib_name[ INI_MAX_PROPERTY_VALUE + 1 ];
    char driver_name[ INI_MAX_PROPERTY_VALUE + 1 ];
    char in_str[ BUFFER_LEN ];
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ], s2[ 100 + LOG_MESSAGE_LEN ];
    SQLWCHAR *uc_in_str;
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

				if ( CHECK_SQLBROWSECONNECTW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLBROWSECONNECTW( parent_connection, 
							connection, 
							conn_str_in,
							len_conn_str_in,
							conn_str_out,
							conn_str_out_max,
							ptr_conn_str_out );
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
\n\t\t\tStr In = %s\
\n\t\t\tStr Out = %s\
\n\t\t\tPtr Conn Str Out = %p",
                connection,
                __wstring_with_length( s1, conn_str_in, len_conn_str_in ), 
                __wstring_with_length( s2, conn_str_out, conn_str_out_max ), 
                ptr_conn_str_out );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
    }