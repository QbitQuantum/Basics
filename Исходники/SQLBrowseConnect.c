SQLRETURN SQLBrowseConnectA(
    SQLHDBC            hdbc,
    SQLCHAR            *conn_str_in,
    SQLSMALLINT        len_conn_str_in,
    SQLCHAR            *conn_str_out,
    SQLSMALLINT        conn_str_out_max,
    SQLSMALLINT        *ptr_conn_str_out )
{
    return SQLBrowseConnect( hdbc, 
                            conn_str_in, 
                            len_conn_str_in,
                            conn_str_out,
                            conn_str_out_max,
                            ptr_conn_str_out );
}