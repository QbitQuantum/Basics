SQLRETURN CLSetConnectOption( SQLHDBC connection_handle,
           SQLUSMALLINT option,
           SQLULEN value )
{
    CLHDBC cl_connection = (CLHDBC) connection_handle; 

    return SQLSETCONNECTOPTION( cl_connection,
           cl_connection -> driver_dbc,
           option,
           value );
}