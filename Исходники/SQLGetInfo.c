SQLRETURN __SQLGetInfo( SQLHDBC connection_handle,
           SQLUSMALLINT info_type,
           SQLPOINTER info_value,
           SQLSMALLINT buffer_length,
           SQLSMALLINT *string_length )
{
    DMHDBC connection = (DMHDBC)connection_handle;
    SQLRETURN ret = SQL_SUCCESS;
    int type;
	SQLUSMALLINT sval;
    char txt[ 30 ], *cptr;
    SQLPOINTER *ptr;

    switch ( info_type )
    {
      case SQL_DATA_SOURCE_NAME:
        type = 1;
        cptr = connection -> dsn;
        break;

      case SQL_DM_VER:
        type = 1;
        sprintf( txt, "%02d.%02d.%04d.%04d",
                SQL_SPEC_MAJOR, SQL_SPEC_MINOR, 
                atoi( VERSION ), atoi( VERSION + 2 ));
        cptr = txt;
        break;

      case SQL_ODBC_VER:
        type = 1;
        sprintf( txt, "%02d.%02d",
                SQL_SPEC_MAJOR, SQL_SPEC_MINOR );
        cptr = txt;
        break;

      case SQL_DRIVER_HDBC:
        type = 2;
        ptr = (SQLPOINTER) connection -> driver_dbc;
        break;

      case SQL_DRIVER_HENV:
        type = 2;
        ptr = (SQLPOINTER) connection -> driver_env;
        break;

      case SQL_DRIVER_HDESC:
        {
            if ( info_value ) 
            {
                DMHDESC hdesc = *((DMHDESC*) info_value); 

                type = 2;

                if ( __validate_desc( hdesc ))
                {
                    ptr = (SQLPOINTER) hdesc -> driver_desc;
                }
                else
                {
                    dm_log_write( __FILE__, 
                            __LINE__, 
                            LOG_INFO, 
                            LOG_INFO, 
                            "Error: HY024" );
    
                    __post_internal_error( &connection -> error,
                            ERROR_HY024, NULL,
                            connection -> environment -> requested_version );

                    return SQL_ERROR;
                }
            }
        }
        break;

      case SQL_DRIVER_HLIB:
        type = 2;
        ptr = connection -> dl_handle;
        break;

      case SQL_DRIVER_HSTMT:
        {
            if ( info_value ) 
            {
                DMHSTMT hstmt = *((DMHSTMT*) info_value); 

                type = 2;

                if ( __validate_stmt( hstmt ))
                {
                    ptr = (SQLPOINTER) hstmt -> driver_stmt;
                }
                else
                {
                    dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: HY024" );

                    __post_internal_error( &connection -> error,
                        ERROR_HY024, NULL,
                        connection -> environment -> requested_version );

                    return SQL_ERROR;
                }
            }
        }
        break;

      case SQL_XOPEN_CLI_YEAR:
        type = 1;
        cptr = connection -> cli_year;
        break;

	  case SQL_ATTR_DRIVER_THREADING:
		type = 3;
		sval = connection -> threading_level;
		break;

      default:
        /*
         * pass all the others on
         */

        if ( connection -> unicode_driver )
        {
            SQLWCHAR *s1 = NULL;

            if ( !CHECK_SQLGETINFOW( connection ))
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: IM001" );

                __post_internal_error( &connection -> error,
                        ERROR_IM001, NULL,
                        connection -> environment -> requested_version );

                return SQL_ERROR;
            }

            switch( info_type )
            {
              case SQL_ACCESSIBLE_PROCEDURES:
              case SQL_ACCESSIBLE_TABLES:
              case SQL_CATALOG_NAME:
              case SQL_CATALOG_NAME_SEPARATOR:
              case SQL_CATALOG_TERM:
              case SQL_COLLATION_SEQ:
              case SQL_COLUMN_ALIAS:
              case SQL_DATA_SOURCE_NAME:
              case SQL_DATA_SOURCE_READ_ONLY:
              case SQL_DATABASE_NAME:
              case SQL_DBMS_NAME:
              case SQL_DBMS_VER:
              case SQL_DESCRIBE_PARAMETER:
              case SQL_DRIVER_NAME:
              case SQL_DRIVER_ODBC_VER:
              case SQL_DRIVER_VER:
              case SQL_ODBC_VER:
              case SQL_EXPRESSIONS_IN_ORDERBY:
              case SQL_IDENTIFIER_QUOTE_CHAR:
              case SQL_INTEGRITY:
              case SQL_KEYWORDS:
              case SQL_LIKE_ESCAPE_CLAUSE:
              case SQL_MAX_ROW_SIZE_INCLUDES_LONG:
              case SQL_MULT_RESULT_SETS:
              case SQL_MULTIPLE_ACTIVE_TXN:
              case SQL_NEED_LONG_DATA_LEN:
              case SQL_ORDER_BY_COLUMNS_IN_SELECT:
              case SQL_PROCEDURE_TERM:
              case SQL_PROCEDURES:
              case SQL_ROW_UPDATES:
              case SQL_SCHEMA_TERM:
              case SQL_SEARCH_PATTERN_ESCAPE:
              case SQL_SERVER_NAME:
              case SQL_SPECIAL_CHARACTERS:
              case SQL_TABLE_TERM:
              case SQL_USER_NAME:
              case SQL_XOPEN_CLI_YEAR:
              case SQL_OUTER_JOINS:
                if ( info_value && buffer_length > 0 )
                {
					buffer_length = sizeof( SQLWCHAR ) * ( buffer_length + 1 );
                    s1 = malloc( buffer_length );
                }
                break;
            }

            ret = SQLGETINFOW( connection,
                    connection -> driver_dbc,
                    info_type,
                    s1 ? s1 : info_value,
                    buffer_length,
                    string_length );

            switch( info_type )
            {
              case SQL_ACCESSIBLE_PROCEDURES:
              case SQL_ACCESSIBLE_TABLES:
              case SQL_CATALOG_NAME:
              case SQL_CATALOG_NAME_SEPARATOR:
              case SQL_CATALOG_TERM:
              case SQL_COLLATION_SEQ:
              case SQL_COLUMN_ALIAS:
              case SQL_DATA_SOURCE_NAME:
              case SQL_DATA_SOURCE_READ_ONLY:
              case SQL_DATABASE_NAME:
              case SQL_DBMS_NAME:
              case SQL_DBMS_VER:
              case SQL_DESCRIBE_PARAMETER:
              case SQL_DRIVER_NAME:
              case SQL_DRIVER_ODBC_VER:
              case SQL_DRIVER_VER:
              case SQL_ODBC_VER:
              case SQL_EXPRESSIONS_IN_ORDERBY:
              case SQL_IDENTIFIER_QUOTE_CHAR:
              case SQL_INTEGRITY:
              case SQL_KEYWORDS:
              case SQL_LIKE_ESCAPE_CLAUSE:
              case SQL_MAX_ROW_SIZE_INCLUDES_LONG:
              case SQL_MULT_RESULT_SETS:
              case SQL_MULTIPLE_ACTIVE_TXN:
              case SQL_NEED_LONG_DATA_LEN:
              case SQL_ORDER_BY_COLUMNS_IN_SELECT:
              case SQL_PROCEDURE_TERM:
              case SQL_PROCEDURES:
              case SQL_ROW_UPDATES:
              case SQL_SCHEMA_TERM:
              case SQL_SEARCH_PATTERN_ESCAPE:
              case SQL_SERVER_NAME:
              case SQL_SPECIAL_CHARACTERS:
              case SQL_TABLE_TERM:
              case SQL_USER_NAME:
              case SQL_XOPEN_CLI_YEAR:
              case SQL_OUTER_JOINS:
                if ( SQL_SUCCEEDED( ret ) && info_value && s1 )
                {
                    unicode_to_ansi_copy( info_value, buffer_length, s1, SQL_NTS, connection, NULL  );
                }
				if ( SQL_SUCCEEDED( ret ) && string_length && info_value ) 
				{
					*string_length = strlen(info_value);
				}
                break;
            }
            if ( s1 )
            {
                free( s1 );
            }
        }
        else
        {
            if ( !CHECK_SQLGETINFO( connection ))
            {
                dm_log_write( __FILE__, 
                        __LINE__, 
                        LOG_INFO, 
                        LOG_INFO, 
                        "Error: IM001" );

                __post_internal_error( &connection -> error,
                        ERROR_IM001, NULL,
                        connection -> environment -> requested_version );

                return SQL_ERROR;
            }

            ret = SQLGETINFO( connection,
                    connection -> driver_dbc,
                    info_type,
                    info_value,
                    buffer_length,
                    string_length );
        }

        return ret;
    }

    if ( type == 1 )
    {
        if ( string_length )
            *string_length = strlen( cptr );

        if ( info_value )
        {
            if ( buffer_length > strlen( cptr ) + 1 )
            {
                strcpy( info_value, cptr );
            }
            else
            {
                memcpy( info_value, cptr, buffer_length - 1 );
                ((char*)info_value)[ buffer_length - 1 ] = '\0';
                ret = SQL_SUCCESS_WITH_INFO;
            }
        }
    }
    else if ( type == 2 )
    {
        if ( info_value )
            *((void **)info_value) = ptr;

        if ( string_length )
            *string_length = sizeof( SQLPOINTER );
    }
	else if ( type == 3 ) 
	{
        if ( info_value )
            *((SQLUSMALLINT *)info_value) = sval;

        if ( string_length )
            *string_length = sizeof( SQLUSMALLINT );
	}

    return ret;
}