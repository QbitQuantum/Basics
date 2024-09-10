SQLRETURN SQLDriverConnectW(
    SQLHDBC            hdbc,
    SQLHWND            hwnd,
    SQLWCHAR            *conn_str_in,
    SQLSMALLINT        len_conn_str_in,
    SQLWCHAR            *conn_str_out,
    SQLSMALLINT        conn_str_out_max,
    SQLSMALLINT        *ptr_conn_str_out,
    SQLUSMALLINT       driver_completion )
{
    DMHDBC connection = (DMHDBC)hdbc;
    struct con_struct con_struct;
    char *driver = NULL, *dsn = NULL;
    char lib_name[ INI_MAX_PROPERTY_VALUE + 1 ];
    char driver_name[ INI_MAX_PROPERTY_VALUE + 1 ];
    SQLRETURN ret_from_connect;
    SQLCHAR s1[ 2048 ];
    int warnings;

    /*
     * check connection
     */

    strcpy( driver_name, "" );

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

				if ( CHECK_SQLDRIVERCONNECTW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLDRIVERCONNECTW( parent_connection, 
							connection, 
							hwnd, 
							conn_str_in, 
							len_conn_str_in,
							conn_str_out,
							conn_str_out_max,
							ptr_conn_str_out,
							driver_completion );
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
            \n\t\t\tWindow Hdl = %p\
            \n\t\t\tStr In = %s\
            \n\t\t\tStr Out = %p\
            \n\t\t\tStr Out Max = %d\
            \n\t\t\tStr Out Ptr = %p\
            \n\t\t\tCompletion = %d",
                connection,
                hwnd,
                __wstring_with_length_hide_pwd( s1, conn_str_in, 
                    len_conn_str_in ), 
                conn_str_out,
                conn_str_out_max,
                ptr_conn_str_out,
                driver_completion );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
    }