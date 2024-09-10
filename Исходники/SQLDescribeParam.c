SQLRETURN CLDescribeParam(
    SQLHSTMT           statement_handle,
    SQLUSMALLINT       ipar,
    SQLSMALLINT        *pf_sql_type,
    SQLUINTEGER        *pcb_param_def,
    SQLSMALLINT        *pib_scale,
    SQLSMALLINT        *pf_nullable )
{
    CLHSTMT cl_statement = (CLHSTMT) statement_handle; 

    return SQLDESCRIBEPARAM( cl_statement -> cl_connection,
            cl_statement -> driver_stmt,
            ipar,
            pf_sql_type,
            pcb_param_def,
            pib_scale,
            pf_nullable );
}