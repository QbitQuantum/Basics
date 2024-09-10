SQLRETURN CLEndTran( SQLSMALLINT handle_type,
                     SQLHANDLE handle,
                     SQLSMALLINT completion_type )
{
    switch ( handle_type )
    {
    case SQL_HANDLE_ENV:
        /*
         * the driver manager will not call this
         */
        return SQL_ERROR;
        break;

    case SQL_HANDLE_DBC:
    {
        CLHDBC cl_connection = (CLHDBC) handle;

        return SQLENDTRAN( cl_connection,
                           SQL_HANDLE_DBC,
                           cl_connection -> driver_dbc,
                           completion_type );
    }
    break;

    default:
        return SQL_ERROR;
    }
}