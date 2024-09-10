SQLRETURN __SQLFreeHandle( SQLSMALLINT handle_type,
        SQLHANDLE handle )
{
    switch( handle_type )
    {
      case SQL_HANDLE_ENV:
        {
            DMHENV environment = (DMHENV)handle;

            /*
             * check environment
             */

            if ( !__validate_env( environment ))
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: SQL_INVALID_HANDLE" );

                return SQL_INVALID_HANDLE;
            }
            
            function_entry( environment );

            if ( log_info.log_flag )
            {
                sprintf( environment -> msg,
                        "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                        handle_type,
                        (void*)handle );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        environment -> msg );
            }

            thread_protect( SQL_HANDLE_ENV, environment );

            /*
             * check states
             */
            if ( environment -> state != STATE_E1 )
            {
                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        "Error: HY010" );

                __post_internal_error( &environment -> error,
                        ERROR_HY010, NULL,
                        environment -> requested_version );

                return function_return( SQL_HANDLE_ENV, environment, SQL_ERROR );
            }

            thread_release( SQL_HANDLE_ENV, environment );

            __release_env( environment );
            return SQL_SUCCESS;
        }
        break;

      case SQL_HANDLE_DBC:
        {
            DMHDBC connection = (DMHDBC)handle;
            DMHENV environment;

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

                return SQL_INVALID_HANDLE;
            }

            function_entry( connection );

            environment = connection -> environment;

            if ( log_info.log_flag )
            {
                sprintf( connection -> msg,
                        "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                        handle_type,
                        (void*)handle );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        connection -> msg );
            }

            thread_protect( SQL_HANDLE_ENV, environment );

            /*
             * check states
             */
            if ( connection -> state != STATE_C2 )
            {
                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        "Error: HY010" );

                __post_internal_error( &connection -> error,
                        ERROR_HY010, NULL,
                        connection -> environment -> requested_version );

                return function_return( SQL_HANDLE_ENV, environment, SQL_ERROR );
            }

            environment -> connection_count --;

            if ( environment -> connection_count == 0 )
            {
                environment -> state = STATE_E1;
            }

            environment = connection -> environment;

            __release_attr_str( &connection -> env_attribute );
            __release_attr_str( &connection -> dbc_attribute );
            __release_attr_str( &connection -> stmt_attribute );

            __disconnect_part_one( connection );

            __release_dbc( connection );

            if ( log_info.log_flag )
            {
                sprintf( environment -> msg,
                        "\n\t\tExit:[SQL_SUCCESS]" );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        environment -> msg );
            }
#if defined ( COLLECT_STATS ) && defined( HAVE_SYS_SEM_H )
            uodbc_update_stats(environment->sh, UODBC_STATS_TYPE_HDBC,
                               (void *)-1);
#endif

            thread_release( SQL_HANDLE_ENV, environment );

            return SQL_SUCCESS;
        }
        break;

      case SQL_HANDLE_STMT:
        {
            DMHSTMT statement = (DMHSTMT)handle;
            DMHDBC connection;
            SQLRETURN ret;

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

                return SQL_INVALID_HANDLE;
            }

            function_entry( statement );

            connection = statement -> connection;

            if ( log_info.log_flag )
            {
                sprintf( statement -> msg,
                        "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                        handle_type,
                        (void*)handle );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        statement -> msg );
            }

            thread_protect( SQL_HANDLE_STMT, statement );

            /*
             * check states
             */
            if ( statement -> state == STATE_S8 ||
                    statement -> state == STATE_S9 ||
                    statement -> state == STATE_S10 ||
                    statement -> state == STATE_S11 ||
                    statement -> state == STATE_S12 )
            {
                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        "Error: HY010" );

                __post_internal_error( &statement -> error,
                          ERROR_HY010, NULL,
                          statement -> connection -> environment -> requested_version );

                return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
            }

            if ( !CHECK_SQLFREEHANDLE( statement -> connection ))
            {
                if ( !CHECK_SQLFREESTMT( statement -> connection ))
                {
                    dm_log_write( __FILE__,
                            __LINE__,
                            LOG_INFO,
                            LOG_INFO,
                            "Error: IM001" );

                    __post_internal_error( &statement -> error,
                            ERROR_IM001, NULL,
                            statement -> connection -> environment -> requested_version );

                    return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
                }
                else
                {
                    ret = SQLFREESTMT( statement -> connection,
                        statement -> driver_stmt,
                        SQL_DROP );
                }
            }
            else
            {
                ret = SQLFREEHANDLE( statement -> connection,
                        handle_type,
                        statement -> driver_stmt );
            }

            if ( SQL_SUCCEEDED( ret ))
            {
                /*
                 * break any association
                 */

                if ( statement -> ard ) {
                    statement -> ard -> associated_with = NULL;
                }
                if ( statement -> apd ) {
                    statement -> apd -> associated_with = NULL;
                }
                /*
                 * release the implicit descriptors, 
				 * this matches the tests in SQLAllocHandle
                 */
                if (( statement -> connection -> driver_act_ver == 3 &&
						CHECK_SQLGETSTMTATTR( connection )) ||
						CHECK_SQLGETSTMTATTRW( connection ))
                {
                    if ( statement -> implicit_ard )
                        __release_desc( statement -> implicit_ard );
                    if ( statement -> implicit_apd )
                        __release_desc( statement -> implicit_apd );
                    if ( statement -> implicit_ird )
                        __release_desc( statement -> implicit_ird );
                    if ( statement -> implicit_ipd )
                        __release_desc( statement -> implicit_ipd );
                }
                statement -> connection -> statement_count --;

                thread_release( SQL_HANDLE_STMT, statement );
#if defined ( COLLECT_STATS ) && defined( HAVE_SYS_SEM_H )
                uodbc_update_stats(connection->environment->sh,
                                   UODBC_STATS_TYPE_HSTMT, (void *)-1);
#endif

                __release_stmt( statement );
            }
            else
            {
                thread_release( SQL_HANDLE_STMT, statement );
            }

            if ( log_info.log_flag )
            {
                sprintf( connection -> msg,
                        "\n\t\tExit:[SQL_SUCCESS]" );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        connection -> msg );
            }

            return function_return( IGNORE_THREAD, connection, ret ); 
        }
        break;

      case SQL_HANDLE_DESC:
        {
            DMHDESC descriptor = (DMHDESC)handle;
            DMHDBC connection;
            SQLRETURN ret;

            /*
             * check descriptor
             */
            if ( !__validate_desc( descriptor ))
            {
                return SQL_INVALID_HANDLE;
            }

            function_entry( descriptor );

            connection = descriptor -> connection;

            if ( log_info.log_flag )
            {
                sprintf( descriptor -> msg,
                        "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                        handle_type,
                        (void*)handle );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        descriptor -> msg );
            }

			if ( descriptor -> implicit )
			{
				dm_log_write( __FILE__,
						__LINE__,
						LOG_INFO,
						LOG_INFO,
						"Error: HY017" );
		
				__post_internal_error( &descriptor -> error,
						ERROR_HY017, NULL,
						connection -> environment -> requested_version );
		
				return function_return( IGNORE_THREAD, descriptor, SQL_ERROR );
			}
		
            thread_protect( SQL_HANDLE_DESC, descriptor );

            if ( !CHECK_SQLFREEHANDLE( connection ))
            {
                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        "Error: IM001" );

                __post_internal_error( &descriptor -> error,
                        ERROR_IM001, NULL,
                        connection -> environment -> requested_version );

                return function_return( SQL_HANDLE_DESC, descriptor, SQL_ERROR );
            }
            else
            {
                ret = SQLFREEHANDLE( connection,
                        handle_type,
                        descriptor -> driver_desc );
            }

            /*
             * check status of statements associated with this descriptor
             */

            if( __check_stmt_from_desc( descriptor, STATE_S8 ) ||
                __check_stmt_from_desc( descriptor, STATE_S9 ) ||
                __check_stmt_from_desc( descriptor, STATE_S10 ) ||
                __check_stmt_from_desc( descriptor, STATE_S11 ) ||
                __check_stmt_from_desc( descriptor, STATE_S12 )) {

                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY010" );

                __post_internal_error( &descriptor -> error,
                        ERROR_HY010, NULL,
                        descriptor -> connection -> environment -> requested_version );

                return function_return( SQL_HANDLE_DESC, descriptor, SQL_ERROR );
            }

            thread_release( SQL_HANDLE_DESC, descriptor );

            __release_desc( descriptor );

            if ( log_info.log_flag )
            {
                sprintf( connection -> msg,
                        "\n\t\tExit:[SQL_SUCCESS]" );

                dm_log_write( __FILE__,
                        __LINE__,
                        LOG_INFO,
                        LOG_INFO,
                        connection -> msg );
            }
#if defined ( COLLECT_STATS ) && defined( HAVE_SYS_SEM_H )
            uodbc_update_stats(connection->environment->sh,
                               UODBC_STATS_TYPE_HDESC, (void *)-1);
#endif

            return function_return( IGNORE_THREAD, connection, SQL_SUCCESS ); 
        }
        break;

      default:
        /*
         * there is nothing to report a error on
         */
        return SQL_ERROR;
    }
}