SQLRETURN SQLPrimaryKeysW(
    SQLHSTMT           statement_handle,
    SQLWCHAR            *sz_catalog_name,
    SQLSMALLINT        cb_catalog_name,
    SQLWCHAR            *sz_schema_name,
    SQLSMALLINT        cb_schema_name,
    SQLWCHAR            *sz_table_name,
    SQLSMALLINT        cb_table_name )
{
    DMHSTMT statement = (DMHSTMT) statement_handle;
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ], s2[ 100 + LOG_MESSAGE_LEN ], s3[ 100 + LOG_MESSAGE_LEN ];

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

				if ( CHECK_SQLPRIMARYKEYSW( parent_statement -> connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

                	return  SQLPRIMARYKEYSW( parent_statement -> connection,
							statement_handle,
    						sz_catalog_name,
    						cb_catalog_name,
    						sz_schema_name,
    						cb_schema_name,
    						sz_table_name,
    						cb_table_name );
				}
			}
		}
#endif
        return SQL_INVALID_HANDLE;
    }

    function_entry( statement );

    if ( log_info.log_flag )
    {
        sprintf( statement -> msg, "\n\t\tEntry:\
\n\t\t\tStatement = %p\
\n\t\t\tCatalog Name = %s\
\n\t\t\tSchema Name = %s\
\n\t\t\tTable Type = %s", 
                statement,
                __wstring_with_length( s1, sz_catalog_name, cb_catalog_name ), 
                __wstring_with_length( s2, sz_schema_name, cb_schema_name ), 
                __wstring_with_length( s3, sz_table_name, cb_table_name ));

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                statement -> msg );
    }