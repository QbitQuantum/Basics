SQLRETURN CLDescribeCol( SQLHSTMT statement_handle,
           SQLUSMALLINT column_number,
           SQLCHAR *column_name,
           SQLSMALLINT buffer_length,
           SQLSMALLINT *name_length,
           SQLSMALLINT *data_type,
           SQLULEN *column_size,
           SQLSMALLINT *decimal_digits,
           SQLSMALLINT *nullable )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 

    return SQLDESCRIBECOL( cl_statement -> cl_connection,
           cl_statement -> driver_stmt,
           column_number,
           column_name,
           buffer_length,
           name_length,
           data_type,
           column_size,
           decimal_digits,
           nullable );
}