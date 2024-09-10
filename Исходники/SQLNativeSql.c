SQLRETURN CLNativeSql(
    SQLHDBC            connection_handle,
    SQLCHAR            *sz_sql_str_in,
    SQLINTEGER         cb_sql_str_in,
    SQLCHAR            *sz_sql_str,
    SQLINTEGER         cb_sql_str_max,
    SQLINTEGER         *pcb_sql_str )
{
    CLHDBC cl_connection = (CLHDBC) connection_handle; 

    /*
     * the cursor lib will take a part in this
     */

    return SQLNATIVESQL( cl_connection,
           cl_connection -> driver_dbc,
           sz_sql_str_in,
           cb_sql_str_in,
           sz_sql_str,
           cb_sql_str_max,
           pcb_sql_str );
}