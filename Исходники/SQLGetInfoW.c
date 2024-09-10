SQLRETURN SQLGetInfoW( SQLHDBC connection_handle,
           SQLUSMALLINT info_type,
           SQLPOINTER info_value,
           SQLSMALLINT buffer_length,
           SQLSMALLINT *string_length )
{
    DMHDBC connection = (DMHDBC)connection_handle;
    SQLRETURN ret = SQL_SUCCESS;
    int type;
    char txt[ 30 ], *cptr;
    SQLPOINTER *ptr;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ];
	SQLUSMALLINT sval;

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

				if ( CHECK_SQLGETINFOW( parent_connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

					return SQLGETINFOW( parent_connection, 
							connection_handle, 
           					info_type,
           					info_value,
           					buffer_length,
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
\n\t\t\tInfo Type = %s\
\n\t\t\tInfo Value = %p\
\n\t\t\tBuffer Length = %d\
\n\t\t\tStrLen = %p",
                connection,
                __info_as_string( s1, info_type ),
                info_value, 
                (int)buffer_length,
                (void*)string_length );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
    }