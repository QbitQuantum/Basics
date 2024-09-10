SQLRETURN CLSetStmtOption( SQLHSTMT statement_handle,
           SQLUSMALLINT option,
           SQLULEN value )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
    SQLUINTEGER val;
    SQLRETURN ret = SQL_SUCCESS;

    switch( option )
    {
      case SQL_CONCURRENCY:
        val = ( SQLUINTEGER ) value;
        if ( cl_statement -> concurrency == SQL_CURSOR_FORWARD_ONLY )
        {
            if ( val != SQL_CONCUR_READ_ONLY )
            {
                ret = SQL_SUCCESS_WITH_INFO;
            }
        }
        else
        {
            if ( val != SQL_CONCUR_READ_ONLY &&
                    val != SQL_CONCUR_VALUES )
            {
                ret = SQL_SUCCESS_WITH_INFO;
            }
        }
        if ( ret == SQL_SUCCESS )
        {
            cl_statement -> concurrency = ( SQLUINTEGER ) value;
        }
        break;
        
      case SQL_CURSOR_TYPE:
        val = ( SQLUINTEGER ) value;
        if ( val != SQL_CURSOR_FORWARD_ONLY &&
                val != SQL_CURSOR_TYPE )
        {
            ret = SQL_SUCCESS_WITH_INFO;
        }
        else
        {
            cl_statement -> cursor_type = ( SQLUINTEGER ) value;
        }
        break;

      case SQL_BIND_TYPE:
        cl_statement -> row_bind_type = ( SQLUINTEGER ) value;
        break;

      case SQL_GET_BOOKMARK:
        cl_statement -> use_bookmarks = ( SQLUINTEGER ) value;
        break;

      case SQL_ROWSET_SIZE:
        cl_statement -> rowset_size = ( SQLUINTEGER ) value;
        break;

      case SQL_SIMULATE_CURSOR:
        val = ( SQLUINTEGER ) value;
        if ( val != SQL_SC_NON_UNIQUE )
        {
            ret = SQL_SUCCESS_WITH_INFO;
        }
        else
        {
            cl_statement -> simulate_cursor = ( SQLUINTEGER ) value;
        }
        break;

      case SQL_ATTR_PARAM_BIND_OFFSET_PTR:
        cl_statement -> param_bind_offset_ptr = ( SQLPOINTER ) value;
        break;

      case SQL_ATTR_PARAM_BIND_TYPE:
        cl_statement -> concurrency = ( SQLUINTEGER ) value;
        break;

      case SQL_ATTR_ROW_BIND_OFFSET_PTR:
        cl_statement -> row_bind_offset_ptr = ( SQLPOINTER ) value;
        break;

      case SQL_ATTR_ROW_ARRAY_SIZE:
        cl_statement -> rowset_array_size = ( SQLUINTEGER ) value;
        break;

      case SQL_ATTR_ROW_STATUS_PTR:
        cl_statement -> row_status_ptr = ( SQLUSMALLINT * ) value;
        break;

      case SQL_ATTR_ROWS_FETCHED_PTR:
        cl_statement -> rows_fetched_ptr = ( SQLULEN * ) value;
        break;

      case SQL_ATTR_USE_BOOKMARKS:
        cl_statement -> use_bookmarks = ( SQLUINTEGER ) value;
        break;

      default:
        return SQLSETSTMTOPTION( cl_statement -> cl_connection,
               cl_statement -> driver_stmt,
               option,
               value );
    }

    if ( ret == SQL_SUCCESS_WITH_INFO )
    {
        cl_statement -> cl_connection -> dh.__post_internal_error( 
					&cl_statement -> dm_statement -> error,
                    ERROR_01S02, NULL,
                    cl_statement -> dm_statement -> connection -> 
                        environment -> requested_version );
    }
    return ret;
}