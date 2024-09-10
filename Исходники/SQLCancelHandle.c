SQLRETURN SQLCancelHandle( SQLSMALLINT HandleType, SQLHANDLE Handle )
{
    SQLRETURN ret;
    SQLCHAR s1[ 100 + LOG_MESSAGE_LEN ];

    switch ( HandleType ) {
        case SQL_HANDLE_STMT:
            {
                DMHSTMT statement = (DMHSTMT) Handle;
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

                if ( log_info.log_flag )
                {
                    sprintf( statement -> msg, "\n\t\tEntry:\n\t\t\tStatement = %p",
                            statement );

                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            statement -> msg );
                }

#if defined( HAVE_LIBPTH ) || defined( HAVE_LIBPTHREAD ) || defined( HAVE_LIBTHREAD )
                /*
                 * Allow this past the thread checks if the driver is at all thread safe, as SQLCancel can 
                 * be called across threads
                 */
                if ( statement -> connection -> protection_level == 3 ) 
                {
                    thread_protect( SQL_HANDLE_STMT, statement ); 
                }
#endif

                /*
                 * check states
                 */

                if ( !CHECK_SQLCANCEL( statement -> connection ))
                {
                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            "Error: IM001" );

                    __post_internal_error( &statement -> error,
                            ERROR_IM001, NULL,
                            statement -> connection -> environment -> requested_version );

#if defined( HAVE_LIBPTH ) || defined( HAVE_LIBPTHREAD ) || defined( HAVE_LIBTHREAD )
                    if ( statement -> connection -> protection_level == 3 ) 
                    {
                        return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
                    }
                    else 
                    {
                        return function_return( IGNORE_THREAD, statement, SQL_ERROR );
                    }
#else 
                    return function_return( IGNORE_THREAD, statement, SQL_ERROR );
#endif
                }

                ret = SQLCANCEL( statement -> connection,
                        statement -> driver_stmt );

                if ( SQL_SUCCEEDED( ret ))
                {
                    if ( statement -> state == STATE_S8 ||
                        statement -> state == STATE_S9 ||
                        statement -> state == STATE_S10 ||
                        statement -> state == STATE_S13 ||
                        statement -> state == STATE_S14 ||
                        statement -> state == STATE_S10 )
                    {
                        if ( statement -> interupted_func == SQL_API_SQLEXECDIRECT )
                        {
                            statement -> state = STATE_S1;
                        }
                        else if ( statement -> interupted_func == SQL_API_SQLEXECUTE )
                        {
                            if ( statement -> hascols )
                            {
                                statement -> state = STATE_S3;
                            }
                            else
                            {
                                statement -> state = STATE_S2;
                            }
                        }
                        else if ( statement -> interupted_func ==
                                SQL_API_SQLBULKOPERATIONS )
                        {
                            if ( statement -> interupted_state == STATE_S5 ||
                                    statement -> interupted_state == STATE_S6 ||
                                    statement -> interupted_state == STATE_S7 )
                            {
                                statement -> state = STATE_S6;
                                statement -> eod = 0;
                            }
                            else
                            {
                                statement -> state = STATE_S6;
                                statement -> eod = 0;
                            }
                        }
                        else if ( statement -> interupted_func ==
                                SQL_API_SQLSETPOS )
                        {
                            if ( statement -> interupted_state == STATE_S5 ||
                                    statement -> interupted_state == STATE_S6 )
                            {
                                statement -> state = STATE_S6;
                                statement -> eod = 0;
                            }
                            else if ( statement -> interupted_state == STATE_S7 )
                            {
                                statement -> state = STATE_S7;
                            }
                        }
                    }
                    else if ( statement -> state == STATE_S11 ||
                            statement -> state == STATE_S12 )
                    {
                        statement -> state = STATE_S12;
                    }
                    else {  /* Same action as SQLFreeStmt( SQL_CLOSE ) */
                        if ( statement -> state == STATE_S4 )
                        {
                            if ( statement -> prepared )
                                statement -> state = STATE_S2;
                            else
                                statement -> state = STATE_S1;
                        }
                        else
                        {
                            if ( statement -> prepared )
                                statement -> state = STATE_S3;
                            else
                                statement -> state = STATE_S1;
                        }
                        statement -> hascols = 0;
                    }
                }

                if ( log_info.log_flag )
                {
                    sprintf( statement -> msg, 
                            "\n\t\tExit:[%s]",
                                __get_return_status( ret, s1 ));

                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            statement -> msg );
                }

#if defined( HAVE_LIBPTH ) || defined( HAVE_LIBPTHREAD ) || defined( HAVE_LIBTHREAD )
                if ( statement -> connection -> protection_level == 3 ) 
                {
                    return function_return( SQL_HANDLE_STMT, statement, SQL_ERROR );
                }
                else 
                {
                    return function_return( IGNORE_THREAD, statement, ret );
                }
#else
                return function_return( IGNORE_THREAD, statement, ret );
#endif
            }
            break;

        case SQL_HANDLE_DBC:
            {
                DMHDBC connection = (DMHDBC) Handle;
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

                if ( log_info.log_flag )
                {
                    sprintf( connection -> msg, "\n\t\tEntry:\n\t\t\tConnection = %p",
                            connection );

                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            connection -> msg );
                }

                /*
                 * check states
                 */

                if ( !CHECK_SQLCANCELHANDLE( connection ))
                {
                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            "Error: IM001" );

                    __post_internal_error( &connection -> error,
                            ERROR_IM001, NULL,
                            connection -> environment -> requested_version );

                    return function_return( IGNORE_THREAD, connection, SQL_ERROR );
                }

                ret = SQLCANCELHANDLE( connection, SQL_HANDLE_DBC,
                        connection -> driver_dbc );

                /*
                 * The effect this has on connection states is not defined AFAIKS
                 */

                if ( log_info.log_flag )
                {
                    sprintf( connection -> msg, 
                            "\n\t\tExit:[%s]",
                                __get_return_status( ret, s1 ));

                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            connection -> msg );
                }

                return function_return( IGNORE_THREAD, connection, ret );
            }
            break;

        default:
            return SQL_INVALID_HANDLE;
            break;
    }
}