// --------------------------------------------------------------------
// to set attributes specific to a connection
// --------------------------------------------------------------------
RETCODE SQL_API SQLSetConnectAttrW ( SQLHDBC            hdbc,
                                     SQLINTEGER         fAttribute,
                                     SQLPOINTER         rgbValue,
                                     SQLINTEGER         cbValue ) {
    __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "SQLSetConnectAttrW, Attr: %d, DataPtr: %d, DataSize: %d", fAttribute,
                              rgbValue, cbValue ) );
    RETCODE code = SQLSetConnectAttr ( hdbc, fAttribute, rgbValue, cbValue );
    return code;
}