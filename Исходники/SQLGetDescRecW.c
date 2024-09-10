SQLRETURN SQLGetDescRecW( SQLHDESC descriptor_handle,
           SQLSMALLINT rec_number, 
           SQLWCHAR *name,
           SQLSMALLINT buffer_length, 
           SQLSMALLINT *string_length,
           SQLSMALLINT *type, 
           SQLSMALLINT *sub_type, 
           SQLLEN *length, 
           SQLSMALLINT *precision, 
           SQLSMALLINT *scale, 
           SQLSMALLINT *nullable )
{
    /*
     * not quite sure how the descriptor can be
     * allocated to a statement, all the documentation talks
     * about state transitions on statement states, but the
     * descriptor may be allocated with more than one statement
     * at one time. Which one should I check ?
     */
    DMHDESC descriptor = (DMHDESC) descriptor_handle;
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ], s2[ 100 + LOG_MESSAGE_LEN ], s3[ 100 + LOG_MESSAGE_LEN ], s4[ 100 + LOG_MESSAGE_LEN ];
    SQLCHAR s5[ 100 + LOG_MESSAGE_LEN ], s6[ 100 + LOG_MESSAGE_LEN ], s7[ 100 + LOG_MESSAGE_LEN ];
    SQLCHAR s8[ 100 + LOG_MESSAGE_LEN ];


    /*
     * check descriptor
     */

    if ( !__validate_desc( descriptor ))
    {
        dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: SQL_INVALID_HANDLE" );

#ifdef WITH_HANDLE_REDIRECT
		{
			DMHDESC parent_desc;

			parent_desc = find_parent_handle( descriptor, SQL_HANDLE_DESC );

			if ( parent_desc ) {
        		dm_log_write( __FILE__, 
                	__LINE__, 
                    	LOG_INFO, 
                    	LOG_INFO, 
                    	"Info: found parent handle" );

				if ( CHECK_SQLGETDESCRECW( parent_desc -> connection ))
				{
        			dm_log_write( __FILE__, 
                		__LINE__, 
                   		 	LOG_INFO, 
                   		 	LOG_INFO, 
                   		 	"Info: calling redirected driver function" );

                	return  SQLGETDESCRECW( parent_desc -> connection,
							descriptor,
							rec_number,
							name,
							buffer_length,
							string_length,
							type,
							sub_type,
							length,
							precision,
							scale,
							nullable );
				}
			}
		}
#endif
        return SQL_INVALID_HANDLE;
    }

    function_entry( descriptor );

    if ( log_info.log_flag )
    {
        sprintf( descriptor -> msg, "\n\t\tEntry:\
\n\t\t\tDescriptor = %p\
\n\t\t\tRec Number = %d\
\n\t\t\tName = %p\
\n\t\t\tBuffer length = %d\
\n\t\t\tString Length = %p\
\n\t\t\tType = %p\
\n\t\t\tSub Type = %p\
\n\t\t\tLength = %p\
\n\t\t\tPrecision = %p\
\n\t\t\tScale = %p\
\n\t\t\tNullable = %p",
                descriptor,
                rec_number,
                name,
                buffer_length,
                string_length,
                type,
                sub_type,
                length,
                precision,
                scale,
                nullable );

        dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                descriptor -> msg );
    }