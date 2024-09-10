SQLRETURN __SQLAllocHandle( SQLSMALLINT handle_type,
           SQLHANDLE input_handle,
           SQLHANDLE *output_handle,
           SQLINTEGER requested_version )
{
    switch( handle_type )
    {
      case SQL_HANDLE_ENV:
        {
            DMHENV environment;
            char pooling_string[ 128 ];

            if ( !output_handle ) 
            {
                return SQL_ERROR;
            }

            if ( input_handle )
            {
                return SQL_INVALID_HANDLE;
            }

            /*
             * check connection pooling attributes
             */

            SQLGetPrivateProfileString( "ODBC", "Pooling", "0",
				pooling_string, sizeof( pooling_string ), 
                "ODBCINST.INI" );

            if ( pooling_string[ 0 ] == '1' ||
                toupper( pooling_string[ 0 ] ) == 'Y' ||
                ( toupper( pooling_string[ 0 ] ) == 'O' &&
                    toupper( pooling_string[ 1 ] ) == 'N' ))
            {
                pooling_enabled = 1;
            }
            else
            {
                pooling_enabled = 0;
            }

            if ( !( environment = __alloc_env()))
            {
                *output_handle = SQL_NULL_HENV;
                return SQL_ERROR;
            }
            *output_handle = (SQLHANDLE) environment;

            /*
             * setup environment state
             */

            environment -> state = STATE_E1;
            environment -> requested_version = requested_version;
        	environment -> sql_driver_count = -1;

            /*
             * if SQLAllocEnv is called then it's probable that
             * the application wants ODBC2.X type behaviour
             *
             * In this case we don't need to set the version via
             * SQLSetEnvAttr()
             *
             */

            environment -> connection_count = 0;

            return SQL_SUCCESS;
        }
        break;

      case SQL_HANDLE_DBC:
        {
            DMHENV environment = (DMHENV) input_handle;
            DMHDBC connection;

            if ( !__validate_env( environment ))
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: SQL_INVALID_HANDLE" );

                return SQL_INVALID_HANDLE;
            }

            if ( output_handle )
                *output_handle = SQL_NULL_HDBC;

            thread_protect( SQL_HANDLE_ENV, environment );

            function_entry(( void * ) input_handle );

            if ( log_info.log_flag )
            { 
                /*
                 * log that we are here
                 */

                sprintf( environment -> msg, 
                        "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                        handle_type,
                        (void*)input_handle );

                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        environment -> msg );
            }

            if ( !output_handle )
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY009" );

                __post_internal_error( &environment -> error,
                        ERROR_HY009, NULL, 
                        SQL_OV_ODBC3 );

                return function_return( SQL_HANDLE_ENV, environment, SQL_ERROR );
            }

            /*
             * check that a version has been requested
             */

            if ( environment -> requested_version == 0 )
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY010" );

                __post_internal_error( &environment -> error,
                        ERROR_HY010, NULL,
                        SQL_OV_ODBC3 );

                *output_handle = SQL_NULL_HDBC;

                return function_return( SQL_HANDLE_ENV, environment, SQL_ERROR );
            }

            connection = __alloc_dbc();
            if ( !connection )
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY013" );

                __post_internal_error( &environment -> error,
                    ERROR_HY013, NULL,
                    environment -> requested_version );

                *output_handle = SQL_NULL_HDBC;

                return function_return( SQL_HANDLE_ENV, environment, SQL_ERROR );
            }

            /*
             * sort out the states
             */

            connection -> state = STATE_C2;
            if ( environment -> state == STATE_E1 )
            {
                environment -> state = STATE_E2;
            }
            environment -> connection_count ++;
            connection -> environment = environment;

            connection -> cursors = SQL_CUR_DEFAULT;
            connection -> login_timeout = SQL_LOGIN_TIMEOUT_DEFAULT;
            connection -> login_timeout_set = 0;
            connection -> auto_commit = 0;
            connection -> auto_commit_set = 0;
            connection -> auto_commit = 0;
            connection -> auto_commit_set = 0;
            connection -> async_enable = 0;
            connection -> async_enable_set = 0;
            connection -> auto_ipd = 0;
            connection -> auto_ipd_set = 0;
            connection -> connection_timeout = 0;
            connection -> connection_timeout_set = 0;
            connection -> metadata_id = 0;
            connection -> metadata_id_set = 0;
            connection -> packet_size = 0;
            connection -> packet_size_set = 0;
            connection -> quite_mode = 0;
            connection -> quite_mode_set = 0;
            connection -> txn_isolation = 0;
            connection -> txn_isolation_set = 0;
            strcpy( connection -> cli_year, "1995" );

            connection -> env_attribute.count = 0;
            connection -> env_attribute.list = NULL;
            connection -> dbc_attribute.count = 0;
            connection -> dbc_attribute.list = NULL;
            connection -> stmt_attribute.count = 0;
            connection -> stmt_attribute.list = NULL;
            connection -> save_attr = NULL;

#ifdef HAVE_ICONV
            connection -> iconv_cd_uc_to_ascii = (iconv_t)-1;
            connection -> iconv_cd_ascii_to_uc = (iconv_t)-1;
            strcpy( connection -> unicode_string, DEFAULT_ICONV_ENCODING );
#endif

            *output_handle = (SQLHANDLE) connection;

            if ( log_info.log_flag )
            {
                sprintf( environment -> msg, 
                        "\n\t\tExit:[SQL_SUCCESS]\n\t\t\tOutput Handle = %p",
                            connection );

                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        environment -> msg );
            }
#if defined ( COLLECT_STATS ) && defined( HAVE_SYS_SEM_H )
            uodbc_update_stats(environment->sh, UODBC_STATS_TYPE_HDBC,
                               (void *)1);
#endif

            thread_release( SQL_HANDLE_ENV, environment );
            return SQL_SUCCESS;
        }
        break;

      case SQL_HANDLE_STMT:
        {
            SQLRETURN ret, ret1;
            DMHDBC connection = (DMHDBC) input_handle;
            DMHSTMT statement;

            if ( !__validate_dbc( connection ))
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: SQL_INVALID_HANDLE" );

                return SQL_INVALID_HANDLE;
            }

            if ( output_handle )
                *output_handle = SQL_NULL_HSTMT;

            thread_protect( SQL_HANDLE_DBC, connection );

            function_entry(( void * ) input_handle );

            if ( log_info.log_flag )
            {
                sprintf( connection -> msg, 
                    "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                    handle_type,
                    (void*)input_handle );

                dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    connection -> msg );
            }

            if ( !output_handle )
            {
                dm_log_write( __FILE__, 
                       __LINE__, 
                       LOG_INFO, 
                       LOG_INFO, 
                       "Error: HY009" );

                __post_internal_error( &connection -> error,
                        ERROR_HY009, NULL, 
                        connection -> environment -> requested_version  );

                return function_return( SQL_HANDLE_DBC, connection , SQL_ERROR );
            }

            if ( connection -> state == STATE_C1 ||
                    connection -> state == STATE_C2 ||
                    connection -> state == STATE_C3 )
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: 08003" );

                __post_internal_error( &connection -> error,
                        ERROR_08003, NULL,
                        connection -> environment -> requested_version );

                *output_handle = SQL_NULL_HSTMT;

                return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
            }

            statement = __alloc_stmt();
            if ( !statement )
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY013" );

                __post_internal_error( &connection -> error,
                        ERROR_HY013, NULL,
                        connection -> environment -> requested_version );

                *output_handle = SQL_NULL_HSTMT;

                return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
            }

            /*
             * pass the call on
             */

            if ( requested_version >= SQL_OV_ODBC3 )
            {
                if ( CHECK_SQLALLOCHANDLE( connection ))
                {
                    ret = SQLALLOCHANDLE( connection,
                            SQL_HANDLE_STMT,
                            connection -> driver_dbc,
                            &statement -> driver_stmt,
                            statement );

                    if ( !SQL_SUCCEEDED( ret ))
                        __release_stmt( statement );
                }
                else if ( CHECK_SQLALLOCSTMT( connection ))
                {
                    ret = SQLALLOCSTMT( connection,
                            connection -> driver_dbc,
                            &statement -> driver_stmt,
                            statement );

                    if ( !SQL_SUCCEEDED( ret ))
                        __release_stmt( statement );
                }
                else
                {
                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            "Error: IM003" );

                    __post_internal_error( &connection -> error,
                            ERROR_IM003, NULL,
                            connection -> environment -> requested_version );

                    __release_stmt( statement );

                    *output_handle = SQL_NULL_HSTMT;

                    return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                }
            }
            else
            {
                if ( CHECK_SQLALLOCSTMT( connection ))
                {
                    ret = SQLALLOCSTMT( connection,
                            connection -> driver_dbc,
                            &statement -> driver_stmt,
                            statement );

                    if ( !SQL_SUCCEEDED( ret ))
                        __release_stmt( statement );
                }
                else if ( CHECK_SQLALLOCHANDLE( connection ))
                {
                    ret = SQLALLOCHANDLE( connection,
                            SQL_HANDLE_STMT,
                            connection -> driver_dbc,
                            &statement -> driver_stmt,
                            statement );

                    if ( !SQL_SUCCEEDED( ret ))
                        __release_stmt( statement );
                }
                else
                {
                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            "Error: IM003" );

                    __post_internal_error( &connection -> error,
                            ERROR_IM003, NULL,
                            connection -> environment -> requested_version );

                    __release_stmt( statement );

                    *output_handle = SQL_NULL_HSTMT;
                
                    return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                }
            }

            if ( SQL_SUCCEEDED( ret ))
            {
                /*
                 * sort out the states
                 */

                statement -> state = STATE_S1;
                if ( connection -> state == STATE_C4 )
                    connection -> state = STATE_C5;

                __register_stmt ( connection, statement );

                *output_handle = (SQLHANDLE) statement;

                statement -> metadata_id = SQL_FALSE;

                /*
                 * if we are connected to a 3 driver then
                 * we need to get the 4 implicit descriptors
                 * so we know that they are valid
                 */

                if ( connection -> driver_act_ver == 3 &&
                        CHECK_SQLGETSTMTATTR( connection ))
                {
                    DRV_SQLHDESC desc;

                    /*
                     * ARD
                     */

                    ret1 = SQLGETSTMTATTR( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_APP_ROW_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> ard = __alloc_desc();
                        if ( !statement -> ard )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL,
                                    connection -> environment -> requested_version );

                            __release_stmt( statement );

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_ard = statement -> ard;
                        statement -> ard -> implicit = 1;
                        statement -> ard -> associated_with = statement;
                        statement -> ard -> state = STATE_D1i;
                        statement -> ard -> driver_desc = desc;
                        statement -> ard -> connection = connection;
                    }

                    /*
                     * APD
                     */

                    ret1 = SQLGETSTMTATTR( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_APP_PARAM_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> apd = __alloc_desc();
                        if ( !statement -> apd )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL,
                                    connection -> environment -> requested_version );
        
                            __release_stmt( statement );

                            *output_handle = SQL_NULL_HSTMT;

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_apd = statement -> apd;
                        statement -> apd -> implicit = 1;
                        statement -> apd -> associated_with = statement;
                        statement -> apd -> state = STATE_D1i;
                        statement -> apd -> driver_desc = desc;
                        statement -> apd -> connection = connection;
                    }

                    /*
                     * IRD
                     */

                    ret1 = SQLGETSTMTATTR( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_IMP_ROW_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> ird = __alloc_desc();
                        if ( !statement -> ird )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL, 
                                    connection -> environment -> requested_version );

                            __release_stmt( statement );

                            *output_handle = SQL_NULL_HSTMT;

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_ird = statement -> ird;
                        statement -> ird -> implicit = 1;
                        statement -> ird -> associated_with = statement;
                        statement -> ird -> state = STATE_D1i;
                        statement -> ird -> driver_desc = desc;
                        statement -> ird -> connection = connection;
                    }

                    /*
                     * IPD
                     */

                    ret1 = SQLGETSTMTATTR( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_IMP_PARAM_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> ipd = __alloc_desc();
                        if ( !statement -> ipd )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL,
                                    connection -> environment -> requested_version );

                            *output_handle = SQL_NULL_HSTMT;

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_ipd = statement -> ipd;
                        statement -> ipd -> implicit = 1;
                        statement -> ipd -> associated_with = statement;
                        statement -> ipd -> state = STATE_D1i;
                        statement -> ipd -> driver_desc = desc;
                        statement -> ipd -> connection = connection;
                    }
                }
                /* Driver may only have unicode API's */
                else if ( CHECK_SQLGETSTMTATTRW( connection ))
                {
                    DRV_SQLHDESC desc;

                    /*
                     * ARD
                     */

                    ret1 = SQLGETSTMTATTRW( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_APP_ROW_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> ard = __alloc_desc();
                        if ( !statement -> ard )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL,
                                    connection -> environment -> requested_version );

                            __release_stmt( statement );

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_ard = statement -> ard;
                        statement -> ard -> implicit = 1;
                        statement -> ard -> associated_with = statement;
                        statement -> ard -> state = STATE_D1i;
                        statement -> ard -> driver_desc = desc;
                        statement -> ard -> connection = connection;
                    }

                    /*
                     * APD
                     */

                    ret1 = SQLGETSTMTATTRW( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_APP_PARAM_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> apd = __alloc_desc();
                        if ( !statement -> apd )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL,
                                    connection -> environment -> requested_version );
        
                            __release_stmt( statement );

                            *output_handle = SQL_NULL_HSTMT;

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_apd = statement -> apd;
                        statement -> apd -> implicit = 1;
                        statement -> apd -> associated_with = statement;
                        statement -> apd -> state = STATE_D1i;
                        statement -> apd -> driver_desc = desc;
                        statement -> apd -> connection = connection;
                    }

                    /*
                     * IRD
                     */

                    ret1 = SQLGETSTMTATTRW( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_IMP_ROW_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> ird = __alloc_desc();
                        if ( !statement -> ird )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL, 
                                    connection -> environment -> requested_version );

                            __release_stmt( statement );

                            *output_handle = SQL_NULL_HSTMT;

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_ird = statement -> ird;
                        statement -> ird -> implicit = 1;
                        statement -> ird -> associated_with = statement;
                        statement -> ird -> state = STATE_D1i;
                        statement -> ird -> driver_desc = desc;
                        statement -> ird -> connection = connection;
                    }

                    /*
                     * IPD
                     */

                    ret1 = SQLGETSTMTATTRW( connection,
                            statement -> driver_stmt,
                            SQL_ATTR_IMP_PARAM_DESC,
                            &desc,
                            sizeof( desc ),
                            NULL );

                    if ( SQL_SUCCEEDED( ret1 ))
                    {
                        /*
                         * allocate one of our descriptors
                         * to wrap around this
                         */
                        statement -> ipd = __alloc_desc();
                        if ( !statement -> ipd )
                        {
                            dm_log_write( __FILE__, 
                                __LINE__, 
                                LOG_INFO, 
                                LOG_INFO, 
                                "Error: HY013" );

                            __post_internal_error( &connection -> error,
                                    ERROR_HY013, NULL,
                                    connection -> environment -> requested_version );

                            *output_handle = SQL_NULL_HSTMT;

                            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
                        }
                        statement -> implicit_ipd = statement -> ipd;
                        statement -> ipd -> implicit = 1;
                        statement -> ipd -> associated_with = statement;
                        statement -> ipd -> state = STATE_D1i;
                        statement -> ipd -> driver_desc = desc;
                        statement -> ipd -> connection = connection;
                    }
                } 
            }

            /*
             * set any preset statement attributes
             */

            if ( SQL_SUCCEEDED( ret ))
            {
                __set_attributes( statement, SQL_HANDLE_STMT );
            }

            if ( log_info.log_flag )
            {
                sprintf( connection -> msg, 
                        "\n\t\tExit:[SQL_SUCCESS]\n\t\t\tOutput Handle = %p",
                        statement );

                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        connection -> msg );
            }
#if defined ( COLLECT_STATS ) && defined( HAVE_SYS_SEM_H )
            uodbc_update_stats(connection->environment->sh,
                               UODBC_STATS_TYPE_HSTMT, (void *)1);
#endif

            return function_return( SQL_HANDLE_DBC, connection, ret );
        }
        break;

      case SQL_HANDLE_DESC:
        {
        SQLRETURN ret;
        DMHDBC connection = (DMHDBC) input_handle;
        DMHDESC descriptor;

        if ( !__validate_dbc( connection ))
        {
            dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: SQL_INVALID_HANDLE" );

            return SQL_INVALID_HANDLE;
        }

        if ( output_handle )
            *output_handle = SQL_NULL_HDESC;

        thread_protect( SQL_HANDLE_DBC, connection );

        function_entry(( void * ) input_handle );

        if ( log_info.log_flag )
        {
            sprintf( connection -> msg, 
                "\n\t\tEntry:\n\t\t\tHandle Type = %d\n\t\t\tInput Handle = %p",
                handle_type,
                (void*)input_handle );

            dm_log_write( __FILE__, 
                __LINE__, 
                LOG_INFO, 
                LOG_INFO, 
                connection -> msg );
        }

        if ( !output_handle )
        {
            dm_log_write( __FILE__, 
                   __LINE__, 
                   LOG_INFO, 
                   LOG_INFO, 
                   "Error: HY009" );

            __post_internal_error( &connection -> error,
                    ERROR_HY009, NULL, 
                    connection -> environment -> requested_version  );

            return function_return( SQL_HANDLE_DBC, connection , SQL_ERROR );
        }

        if ( connection -> state == STATE_C1 ||
                connection -> state == STATE_C2 ||
                connection -> state == STATE_C3 )
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: 08003" );

            __post_internal_error( &connection -> error,
                    ERROR_08003, NULL,
                    connection -> environment -> requested_version );

            *output_handle = SQL_NULL_HDESC;

            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
        }

        descriptor = __alloc_desc();
        if ( !descriptor )
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: HY013" );

            __post_internal_error( &connection -> error,
                    ERROR_HY013, NULL,
                    connection -> environment -> requested_version );

            *output_handle = SQL_NULL_HDESC;

            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
        }

        /*
         * pass the call on
         */

        if ( CHECK_SQLALLOCHANDLE( connection ))
        {
            ret = SQLALLOCHANDLE( connection,
                    SQL_HANDLE_DESC,
                    connection -> driver_dbc,
                    &descriptor -> driver_desc,
                    NULL );

            if ( !SQL_SUCCEEDED( ret ))
                __release_desc( descriptor );
        }
        else
        {
            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    "Error: IM003" );

            __post_internal_error( &connection -> error,
                    ERROR_IM003, NULL,
                    connection -> environment -> requested_version );

            __release_desc( descriptor );

            *output_handle = SQL_NULL_HDESC;

            return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
        }

        if ( SQL_SUCCEEDED( ret ))
        {
            /*
             * sort out the states
             */

            descriptor -> state = STATE_D1e;
            descriptor -> implicit = 0;
            descriptor -> associated_with = NULL;

            connection -> statement_count ++;

            descriptor -> connection = connection;

            *output_handle = (SQLHANDLE) descriptor;
        }

        if ( log_info.log_flag )
        {
            sprintf( connection -> msg, 
                    "\n\t\tExit:[SQL_SUCCESS]\n\t\t\tOutput Handle = %p",
                    descriptor );

            dm_log_write( __FILE__, 
                    __LINE__, 
                    LOG_INFO, 
                    LOG_INFO, 
                    connection -> msg );
        }
#if defined ( COLLECT_STATS ) && defined( HAVE_SYS_SEM_H )
        uodbc_update_stats(connection->environment->sh, UODBC_STATS_TYPE_HDESC,
                           (void *)1);
#endif

        return function_return( SQL_HANDLE_DBC, connection, ret );
        }
        break;

      default:
		if ( __validate_env( (DMHENV) input_handle ))
		{
			DMHENV environment = (DMHENV) input_handle;

            thread_protect( SQL_HANDLE_ENV, environment );

			__post_internal_error( &environment -> error,
						ERROR_HY092, NULL,
						environment -> requested_version );

			return function_return( SQL_HANDLE_ENV, environment, SQL_ERROR );
		}
		else if ( __validate_dbc( (DMHDBC) input_handle ))
		{
			DMHDBC connection = (DMHDBC) input_handle;

            thread_protect( SQL_HANDLE_DBC, connection );

			__post_internal_error( &connection -> error,
					ERROR_HY092, NULL,
					connection -> environment -> requested_version );
	
			return function_return( SQL_HANDLE_DBC, connection, SQL_ERROR );
		}
		else
		{
			return SQL_ERROR;
		}
		break;
    }
}