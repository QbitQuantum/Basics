SQLRETURN CLGetTypeInfo( SQLHSTMT statement_handle,
           SQLSMALLINT data_type )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 
    SQLRETURN ret;

    ret = SQLGETTYPEINFO( cl_statement -> cl_connection,
           cl_statement -> driver_stmt,
           data_type );

    cl_statement -> not_from_select = 1;

    return ret;
}