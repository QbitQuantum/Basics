SQLRETURN SQLSpecialColumnsW( SQLHSTMT statement_handle,
           SQLUSMALLINT identifier_type,
           SQLWCHAR *catalog_name,
           SQLSMALLINT name_length1,
           SQLWCHAR *schema_name,
           SQLSMALLINT name_length2,
           SQLWCHAR *table_name,
           SQLSMALLINT name_length3,
           SQLUSMALLINT scope,
           SQLUSMALLINT nullable )
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

				if ( CHECK_SQLSPECIALCOLUMNSW( parent_statement -> connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

                	return  SQLSPECIALCOLUMNSW( parent_statement -> connection,
							statement_handle,
           					identifier_type,
           					catalog_name,
           					name_length1,
           					schema_name,
           					name_length2,
           					table_name,
           					name_length3,
           					scope,
           					nullable );
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
            \n\t\t\tIdentifier Type = %d\
            \n\t\t\tCatalog Name = %s\
            \n\t\t\tSchema Name = %s\
            \n\t\t\tTable Name = %s\
            \n\t\t\tScope = %d\
            \n\t\t\tNullable = %d",
                statement,
                identifier_type,
                __wstring_with_length( s1, catalog_name, name_length1 ), 
                __wstring_with_length( s2, schema_name, name_length2 ), 
                __wstring_with_length( s3, table_name, name_length3 ), 
                scope,
                nullable );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                statement -> msg );
    }