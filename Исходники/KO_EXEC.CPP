RETCODE SQL_API SQLExecDirect ( SQLHSTMT    pStmt,
                                SQLCHAR*    pStmtText,
                                SQLINTEGER  pTextLength ) {
    __ODBCLOG ( _ODBCLogMsg ( LogLevel_DEBUG, "SQLExecDirect called, strlen is %d, pTextLength is %d",
                              strlen ( ( char* ) pStmtText ), pTextLength ) );
    unique_ptr<wchar_t[]> pStmtTextW ( char2wchar ( ( char* ) pStmtText ) );
    return SQLExecDirectW ( pStmt, ( SQLWCHAR* ) pStmtTextW.get(), pTextLength );
}