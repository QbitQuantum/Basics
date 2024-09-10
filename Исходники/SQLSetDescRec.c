SQLRETURN SQLSetDescRec( SQLHDESC descriptor_handle,
           SQLSMALLINT rec_number, 
           SQLSMALLINT type,
           SQLSMALLINT subtype, 
           SQLLEN length,
           SQLSMALLINT precision, 
           SQLSMALLINT scale,
           SQLPOINTER data, 
           SQLLEN *string_length,
           SQLLEN *indicator )
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

        return SQL_INVALID_HANDLE;
    }

    function_entry( descriptor );

    thread_protect( SQL_HANDLE_DESC, descriptor );

    if ( descriptor -> connection -> state < STATE_C4 )
    {
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

    if ( !CHECK_SQLSETDESCREC( descriptor -> connection ))
    {
        __post_internal_error( &descriptor -> error,
                ERROR_IM001, NULL,
                descriptor -> connection -> environment -> requested_version );

        return function_return( SQL_HANDLE_DESC, descriptor, SQL_ERROR ); 
    }

    ret = SQLSETDESCREC( descriptor -> connection,
            descriptor -> driver_desc,
            rec_number, 
            type,
            subtype, 
            length,
            precision, 
            scale,
            data, 
            string_length,
            indicator );

    return function_return( SQL_HANDLE_DESC, descriptor, ret );
}