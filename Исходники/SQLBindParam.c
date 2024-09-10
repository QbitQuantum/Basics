SQLRETURN CLBindParam( SQLHSTMT statement_handle,
           SQLUSMALLINT parameter_number,
           SQLSMALLINT value_type,
           SQLSMALLINT parameter_type,
           SQLULEN length_precision,
           SQLSMALLINT parameter_scale,
           SQLPOINTER parameter_value,
           SQLLEN *strlen_or_ind )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 

    return SQLBINDPARAM( cl_statement -> cl_connection,
            cl_statement -> driver_stmt,
           parameter_number,
           value_type,
           parameter_type,
           length_precision,
           parameter_scale,
           parameter_value,
           strlen_or_ind );
}