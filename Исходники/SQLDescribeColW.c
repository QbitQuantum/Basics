SQLRETURN SQLDescribeColW( SQLHSTMT statement_handle,
           SQLUSMALLINT column_number,
           SQLWCHAR *column_name,
           SQLSMALLINT buffer_length,
           SQLSMALLINT *name_length,
           SQLSMALLINT *data_type,
           SQLULEN *column_size,
           SQLSMALLINT *decimal_digits,
           SQLSMALLINT *nullable )
{
    DMHSTMT statement = (DMHSTMT) statement_handle;
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ], s2[ 100 + LOG_MESSAGE_LEN ], s3[ 100 + LOG_MESSAGE_LEN ], s4[ 100 + LOG_MESSAGE_LEN ];
    SQLCHAR s5[ 100 + LOG_MESSAGE_LEN ];
    SQLCHAR s6[ 100 + LOG_MESSAGE_LEN ];

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

				if ( CHECK_SQLDESCRIBECOLW( parent_statement -> connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

                	return  SQLDESCRIBECOLW( parent_statement -> connection,
							statement_handle,
							column_number,
							column_name,
							buffer_length,
							name_length,
							data_type,
							column_size,
							decimal_digits,
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
            \n\t\t\tColumn Number = %d\
            \n\t\t\tColumn Name = %p\
            \n\t\t\tBuffer Length = %d\
            \n\t\t\tName Length = %p\
            \n\t\t\tData Type = %p\
            \n\t\t\tColumn Size = %p\
            \n\t\t\tDecimal Digits = %p\
            \n\t\t\tNullable = %p",
                statement,
                column_number,
                column_name,
                buffer_length,
                name_length,
                data_type,
                column_size,
                decimal_digits,
                nullable );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                statement -> msg );
    }