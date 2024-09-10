SQLRETURN SQLForeignKeysW(
    SQLHSTMT           statement_handle,
    SQLWCHAR            *szpk_catalog_name,
    SQLSMALLINT        cbpk_catalog_name,
    SQLWCHAR            *szpk_schema_name,
    SQLSMALLINT        cbpk_schema_name,
    SQLWCHAR            *szpk_table_name,
    SQLSMALLINT        cbpk_table_name,
    SQLWCHAR            *szfk_catalog_name,
    SQLSMALLINT        cbfk_catalog_name,
    SQLWCHAR            *szfk_schema_name,
    SQLSMALLINT        cbfk_schema_name,
    SQLWCHAR            *szfk_table_name,
    SQLSMALLINT        cbfk_table_name )
{
    DMHSTMT statement = (DMHSTMT) statement_handle;
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ], s2[ 100 + LOG_MESSAGE_LEN ], s3[ 100 + LOG_MESSAGE_LEN ], s4[ 100 + LOG_MESSAGE_LEN ];
    SQLCHAR s5[ 100 + LOG_MESSAGE_LEN ], s6[ 100 + LOG_MESSAGE_LEN ];

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

				if ( CHECK_SQLFOREIGNKEYSW( parent_statement -> connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

                	return  SQLFOREIGNKEYSW( parent_statement -> connection,
							statement,
							szpk_catalog_name, 
							cbpk_catalog_name,
							szpk_schema_name,
							cbpk_schema_name,
							szpk_table_name,
							cbpk_table_name,
							szfk_catalog_name,
							cbfk_catalog_name,
							szfk_schema_name,
							cbfk_schema_name,
							szfk_table_name,
							cbfk_table_name );
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
\n\t\t\tPK Catalog Name = %s\
\n\t\t\tPK Schema Name = %s\
\n\t\t\tPK Table Name = %s\
\n\t\t\tFK Catalog Name = %s\
\n\t\t\tFK Schema Name = %s\
\n\t\t\tFK Table Name = %s",
                statement,
                __wstring_with_length( s1, szpk_catalog_name, cbpk_catalog_name ), 
                __wstring_with_length( s2, szpk_schema_name, cbpk_schema_name ), 
                __wstring_with_length( s3, szpk_table_name, cbpk_table_name ), 
                __wstring_with_length( s4, szfk_catalog_name, cbfk_catalog_name ), 
                __wstring_with_length( s5, szfk_schema_name, cbfk_schema_name ), 
                __wstring_with_length( s6, szfk_table_name, cbfk_table_name ));

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                statement -> msg );
    }